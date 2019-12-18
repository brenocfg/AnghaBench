#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct stat {int st_size; } ;

/* Variables and functions */
 char* FW_NAME ; 
 unsigned char MAGIC ; 
 unsigned int MAGIC_LZMA ; 
 unsigned int MAGIC_PART ; 
 int MAGIC_SZ ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  close (int) ; 
 int creat (char const*,int) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 char getchar () ; 
 scalar_t__ lzma_inflate (unsigned char*,int,unsigned char*,int*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,unsigned char*,int) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 char* part_type (unsigned int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read (int,unsigned char*,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int write (int,unsigned char*,int) ; 

int main(int argc, char **argv)
{
	struct stat s;
	unsigned char *buf_orig;
	unsigned int *buf;
	int buflen;
	int fd;
	int i;
	int err;
	int start = 0, end = 0;

	printf("Arcadyan Firmware cutter v0.1\n");
	printf("-----------------------------\n");
	printf("This tool extracts the different parts of an arcadyan firmware update file\n");
	printf("This tool is for private use only. The Firmware that gets extracted has a license that forbids redistribution\n");
	printf("Please only run this if you understand the risks\n\n");
	printf("I understand the risks ? (y/N)\n");

	if (getchar() != 'y')
		return -1;

	if (stat(FW_NAME, &s) != 0) {
		printf("Failed to find %s\n", FW_NAME);
		printf("Ask Google or try https://www.telekom.de/hilfe/downloads/firmware-speedport-w921v-1.44.000.bin\n");
		return -1;
	}

	buf_orig = malloc(s.st_size);
	buf = malloc(s.st_size);
	if (!buf_orig || !buf) {
		printf("Failed to alloc %d bytes\n", s.st_size);
		return -1;
	}

	fd = open(FW_NAME, O_RDONLY);
	if (fd < 0) {
		printf("Unable to open %s\n", FW_NAME);
		return -1;
	}


	buflen = read(fd, buf_orig, s.st_size);
	close(fd);
	if (buflen != s.st_size) {
		printf("Loaded %d instead of %d bytes inside %s\n", buflen, s.st_size, FW_NAME);
		return -1;
	}

	/* <magic> */
	buf_orig++;
	buflen -= 1;
	for (i = 0; i < MAGIC_SZ; i++) {
		if ((i % 16) < 3)
			buf_orig[i] = buf_orig[i + 16] ^ MAGIC;
		else
			buf_orig[i] = buf_orig[i] ^ MAGIC;
	}
	buflen -= 3;
	memmove(&buf_orig[MAGIC_SZ], &buf_orig[MAGIC_SZ + 3], buflen - MAGIC_SZ);
	memcpy(buf, buf_orig, s.st_size);

	/* </magic> */
	do {
		if (buf[end] == MAGIC_PART) {
			end += 2;
			printf("Found partition at 0x%08X with size %d\n",
				start * sizeof(unsigned int),
				(end - start) * sizeof(unsigned int));
			if (buf[start] == MAGIC_LZMA) {
				int dest_len = 1024 * 1024;
				int len = buf[end - 3];
				unsigned int id = buf[end - 6];
				const char *type = part_type(id);
				unsigned char *dest;

				dest = malloc(dest_len);
				if (!dest) {
					printf("Failed to alloc dest buffer\n");
					return -1;
				}

				if (lzma_inflate((unsigned char*)&buf[start], len, dest, &dest_len)) {
					printf("Failed to decompress data\n");
					return -1;
				}

				fd = creat(type, S_IRUSR | S_IWUSR);
				if (fd != -1) {
					if (write(fd, dest, dest_len) != dest_len)
						printf("\tFailed to write %d bytes\n", dest_len);
					else
						printf("\tWrote %d bytes to %s\n", dest_len, type);
					close(fd);
				} else {
					printf("\tFailed to open %s\n", type);
				}
				free(dest);
			} else {
				printf("\tThis is not lzma\n");
			}
			start = end;
		} else {
			end++;
		}
	} while(end < buflen / sizeof(unsigned int));

	return 0;
}