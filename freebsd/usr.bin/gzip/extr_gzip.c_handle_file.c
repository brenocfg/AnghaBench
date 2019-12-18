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
typedef  int /*<<< orphan*/  outfile ;
typedef  int off_t ;

/* Variables and functions */
 int PATH_MAX ; 
 scalar_t__ cflag ; 
 scalar_t__ dflag ; 
 int file_compress (char*,char*,int) ; 
 int file_uncompress (char*,char*,int) ; 
 int /*<<< orphan*/  infile_clear () ; 
 int /*<<< orphan*/  infile_set (char*,int) ; 
 int /*<<< orphan*/  print_test (char*,int) ; 
 int /*<<< orphan*/  print_verbage (char*,char*,int,int) ; 
 scalar_t__ tflag ; 
 scalar_t__ vflag ; 

__attribute__((used)) static void
handle_file(char *file, struct stat *sbp)
{
	off_t usize, gsize;
	char	outfile[PATH_MAX];

	infile_set(file, sbp->st_size);
	if (dflag) {
		usize = file_uncompress(file, outfile, sizeof(outfile));
#ifndef SMALL
		if (vflag && tflag)
			print_test(file, usize != -1);
#endif
		if (usize == -1)
			return;
		gsize = sbp->st_size;
	} else {
		gsize = file_compress(file, outfile, sizeof(outfile));
		if (gsize == -1)
			return;
		usize = sbp->st_size;
	}
	infile_clear();

#ifndef SMALL
	if (vflag && !tflag)
		print_verbage(file, (cflag) ? NULL : outfile, usize, gsize);
#endif
}