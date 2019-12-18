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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t calculate_digest (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char** o_images ; 
 size_t o_isize ; 
 int /*<<< orphan*/  o_meta ; 
 int /*<<< orphan*/  o_msize ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  verbose (char*,char*,size_t) ; 
 int /*<<< orphan*/  write_checksum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_meta_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_seama_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void pack_files(void)
{
	FILE * fh;
	FILE * ifh;
	size_t i, fsize;
	char filename[512];
	uint8_t digest[16];

	for (i=0; i<o_isize; i++)
	{
		/* Open the input file. */
		ifh = fopen(o_images[i], "r+");
		if (ifh)
		{
			fsize = calculate_digest(ifh, 0, digest);
			verbose("file size (%s) : %d\n", o_images[i], fsize);
			rewind(ifh);

			/* Open the output file. */
			sprintf(filename, "%s.seama", o_images[i]);
			fh = fopen(filename, "w+");
			if (fh)
			{
				write_seama_header(fh, o_meta, o_msize, fsize);
				write_checksum(fh, digest);
				write_meta_data(fh, o_meta, o_msize);
				copy_file(fh, ifh);
				fclose(fh);
			}
			fclose(ifh);
		}
		else
		{
			printf("Unable to open image file '%s'\n",o_images[i]);
		}
	}
}