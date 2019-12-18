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
typedef  int /*<<< orphan*/  md5_state_t ;
typedef  int /*<<< orphan*/  md5_byte_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LVL2 ; 
 int EOF ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int ferror (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fputc (unsigned char,int /*<<< orphan*/ *) ; 
 int fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_version ; 
 int fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 unsigned char* img_eof ; 
 unsigned char* img_hdr ; 
 int /*<<< orphan*/  lprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  md5_append (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  md5_finish (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 char* strerror (int) ; 

int create_img_file(FILE *f_out, char *out_filename, char *zip_filename) {
	int exitcode = 0;

	md5_state_t state;
	md5_byte_t digest[16];

	int i;
	int size;

	FILE *f_in;
	unsigned char buffer[1];

	// copy firmware version
	memcpy(&img_hdr[50], fw_version, 2);

	// clear md5 checksum
	memset(&img_hdr[480], 0, 16);

	// prepare md5 checksum calculation
	md5_init(&state);

	// add img header
	lprintf(DEBUG_LVL2, " adding img header\n");
	for (i = 0; i < 512; i++) {
		size = fputc(img_hdr[i], f_out);
		if (size == EOF) {
			exitcode = ferror(f_out);
			printf("output file %s: %s\n", out_filename, strerror(exitcode));
			break;
		}
		md5_append(&state, (const md5_byte_t *)&img_hdr[i], 1);
	}

	// adding zip file
	if (!exitcode) {
		lprintf(DEBUG_LVL2, " adding zip file\n");
		f_in = fopen(zip_filename, "rb");
		if (!f_in) {
			exitcode = errno;
			printf("input file %s: %s\n", zip_filename, strerror(exitcode));
		} else {
			while ((size = fgetc(f_in)) != EOF) {
				buffer[0] = size;

				size = fputc(buffer[0], f_out);
				if (size == EOF) {
					exitcode = ferror(f_out);
					printf("output file %s: %s\n", out_filename, strerror(exitcode));
					break;
				}
				md5_append(&state, (const md5_byte_t *)buffer, 1);
			}
			if (ferror(f_in)) {
				exitcode = ferror(f_in);
				printf("input file %s: %s\n", zip_filename, strerror(exitcode));
			}
		}

	}

	// add end byte
	if (!exitcode) {
		lprintf(DEBUG_LVL2, " adding img eof byte\n");
		size = fputc(img_eof[0], f_out);
		if (size == EOF) {
			exitcode = ferror(f_out);
			printf("output file %s: %s\n", out_filename, strerror(exitcode));
		}
		md5_append(&state, (const md5_byte_t *)img_eof, 1);
	}

	// append salt to md5 checksum
	md5_append(&state, (const md5_byte_t *)"A^gU*<>?RFY@#DR&Z", 17);

	// finish md5 checksum calculation
	md5_finish(&state, digest);

	// write md5 checksum into img header
	if (!exitcode) {
		lprintf(DEBUG_LVL2, " writing md5 checksum into img header of file\n");

		size = fseek(f_out, 480, SEEK_SET);
		if (size == -1) {
			exitcode = errno;
			printf("output file %s: %s\n", out_filename, strerror(exitcode));
		} else {
			size = fwrite(digest, 16, 1, f_out);
			if (size < 1) {
				if (ferror(f_out)) {
					exitcode = ferror(f_out);
					printf("output file %s: %s\n", out_filename, strerror(exitcode));
				} else {
					exitcode = 1;
					printf("output file %s: unspecified write error\n", out_filename);
				}
			}
		}

		fclose(f_in);
	}

	return exitcode;
}