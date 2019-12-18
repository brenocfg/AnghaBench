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
typedef  int uint32_t ;
struct stat {int st_size; } ;

/* Variables and functions */
 int HEADER_SIZE ; 
 int IH_MAGIC ; 
 int MODEL_LEN ; 
 int NAME_LEN ; 
 size_t OFFSET_ARCH ; 
 size_t OFFSET_COMP ; 
 int OFFSET_DCRC ; 
 int OFFSET_EP ; 
 int OFFSET_HCRC ; 
 int OFFSET_LOAD ; 
 size_t OFFSET_MAC ; 
 int OFFSET_MAGIC ; 
 int OFFSET_MODEL ; 
 int OFFSET_NAME ; 
 size_t OFFSET_OS ; 
 int OFFSET_SIZE ; 
 int OFFSET_TIME ; 
 size_t OFFSET_TYPE ; 
 int OFFSET_VERSION ; 
 int O_CREAT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int S_IRGRP ; 
 int S_IRWXU ; 
 int VERSION_LEN ; 
 int /*<<< orphan*/  be_wr (unsigned char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int crc32 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc (size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,size_t) ; 
 int open (char const*,int,...) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 size_t read (int,unsigned char*,int) ; 
 int stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strncpy (unsigned char*,char*,int) ; 
 size_t write (int,unsigned char*,size_t) ; 

int main(int argc, char **argv)
{
	int fdin;
	int fdout;
	struct stat sb;
	uint32_t filesize;
	uint32_t padding;
	int ret = 0;
	const char *pathin;
	const char *pathout;
	unsigned char *buffer;
	unsigned char *infop;
	uint32_t sum;
	size_t bufsize;
	size_t bytes;
	int i;

	if (argc < 3) {
		printf("Too few arguments.\n");
		printf("%s <infile> <outfile>\n", argv[0]);
	}

	pathin = argv[1];
	pathout = argv[2];

	ret = stat(pathin, &sb);
	if (ret < 0)
		return ret;

	filesize = sb.st_size;
	padding = filesize % 4;
	printf("INFILE: %s, size: %08x bytes\n", pathin, filesize);
	/* File + extended header size */
	bufsize = filesize + HEADER_SIZE;

	printf("Allocate %08x bytes\n", bufsize);
	buffer = malloc(bufsize);
	if (!buffer) {
		printf("OOM: could not allocate buffer\n");
		return 0;
	}

	memset(buffer, 0x00, bufsize);

	/* Read file to buffer */
	fdin = open(pathin, O_RDONLY);
	if (!fdin) {
		printf("ERROR: could not open input file\n");
		return 0;
	}
	bytes = read(fdin, buffer + HEADER_SIZE, filesize);
	if (bytes < filesize) {
		printf("ERROR: could not read entire file\n");
		return 0;
	}
	close(fdin);

	/* PREP HEADER AND FOOTER */
	infop = buffer;

	be_wr(buffer + OFFSET_MAGIC, IH_MAGIC);

	/* FIXME: use actual time */
	be_wr(buffer + OFFSET_TIME, 0x4c06738c);
	be_wr(buffer + OFFSET_SIZE, filesize);

	/* Load address & entry point */
	be_wr(buffer + OFFSET_LOAD, 0x00008000);
	be_wr(buffer + OFFSET_EP, 0x00008000);

	buffer[OFFSET_OS] = 0x05; /* Linux */
	buffer[OFFSET_ARCH] = 0x02; /* ARM */
	buffer[OFFSET_TYPE] = 0x02; /* OS kernel image */
	buffer[OFFSET_COMP] = 0x01; /* gzip */

	/* The vendor firmware just hardcodes this */
	strncpy(buffer + OFFSET_NAME, "kernel.img", NAME_LEN);
	buffer[OFFSET_NAME + NAME_LEN - 1] = '\0';
	strncpy(buffer + OFFSET_MODEL, "dns-313v3", MODEL_LEN);
	buffer[OFFSET_MODEL + MODEL_LEN - 1] = '\0';
	strncpy(buffer + OFFSET_VERSION, "2.01b04", VERSION_LEN);
	buffer[OFFSET_VERSION + VERSION_LEN - 1] = '\0';
	/* Just some MAC address from the example */
	buffer[OFFSET_MAC] = 0x00;
	buffer[OFFSET_MAC + 1] = 0x80;
	buffer[OFFSET_MAC + 2] = 0xc8;
	buffer[OFFSET_MAC + 3] = 0x16;
	buffer[OFFSET_MAC + 4] = 0x81;
	buffer[OFFSET_MAC + 5] = 0x68;

	/* Checksum payload */
	sum = crc32(0, buffer + HEADER_SIZE, filesize);
	be_wr(buffer + OFFSET_DCRC, sum);
	printf("data checksum: 0x%08x\n", sum);

	/* Checksum header, then write that into the header checksum */
	sum = crc32(0, buffer, HEADER_SIZE);
	be_wr(buffer + OFFSET_HCRC, sum);
	printf("header checksum: 0x%08x\n", sum);

	printf("OUTFILE: %s, size: %08x bytes\n", pathout, bufsize);
	fdout = open(pathout, O_RDWR|O_CREAT|O_TRUNC,S_IRWXU|S_IRGRP);
	if (!fdout) {
		printf("ERROR: could not open output file\n");
		return  0;
	}
	bytes = write(fdout, buffer, bufsize);
	if (bytes < bufsize) {
		printf("ERROR: could not write complete output file\n");
		return  0;
	}
	close(fdout);

	free(buffer);

	return 0;
}