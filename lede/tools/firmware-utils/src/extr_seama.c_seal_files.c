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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  copy_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 char** o_images ; 
 size_t o_isize ; 
 int /*<<< orphan*/  o_meta ; 
 int /*<<< orphan*/  o_msize ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ verify_seama (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_meta_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_seama_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void seal_files(const char * file)
{
	FILE * fh;
	FILE * ifh;
	size_t i;

	/* Each image should be seama. */
	for (i = 0; i < o_isize; i++)
	{
		if (verify_seama(o_images[i], 0) < 0)
		{
			printf("'%s' is not a seama file !\n",o_images[i]);
			return;
		}
	}

	/* Open file for write */
	fh = fopen(file, "w+");
	if (fh)
	{
		/* Write the header. */
		write_seama_header(fh, o_meta, o_msize, 0);
		write_meta_data(fh, o_meta, o_msize);

		/* Write image files */
		for (i=0; i<o_isize; i++)
		{
			ifh = fopen(o_images[i], "r+");
			if (ifh)
			{
				copy_file(fh, ifh);
				fclose(ifh);
			}
		}

		fclose(fh);
	}
}