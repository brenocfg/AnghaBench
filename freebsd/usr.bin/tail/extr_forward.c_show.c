#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * fp; int /*<<< orphan*/  file_name; } ;
typedef  TYPE_1__ file_info_t ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ierr (int /*<<< orphan*/ ) ; 
 TYPE_1__* last ; 
 int no_files ; 
 int /*<<< orphan*/  oerr () ; 
 int /*<<< orphan*/  printfn (int /*<<< orphan*/ ,int) ; 
 int putchar (int) ; 
 int /*<<< orphan*/  qflag ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
show(file_info_t *file)
{
	int ch;

	while ((ch = getc(file->fp)) != EOF) {
		if (last != file && no_files > 1) {
			if (!qflag)
				printfn(file->file_name, 1);
			last = file;
		}
		if (putchar(ch) == EOF)
			oerr();
	}
	(void)fflush(stdout);
	if (ferror(file->fp)) {
		fclose(file->fp);
		file->fp = NULL;
		ierr(file->file_name);
		return 0;
	}
	clearerr(file->fp);
	return 1;
}