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
 int /*<<< orphan*/ * compress_program ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 scalar_t__ file_is_tmp (char const*) ; 
 scalar_t__ pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 

void
closefile(FILE *f, const char *fn)
{
	if (f == NULL) {
		;
	} else if (f == stdin) {
		;
	} else if (f == stdout) {
		fflush(f);
	} else {
		if (file_is_tmp(fn) && compress_program != NULL) {
			if(pclose(f)<0)
				err(2,NULL);
		} else
			fclose(f);
	}
}