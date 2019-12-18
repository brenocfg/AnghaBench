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
 int EOF ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 scalar_t__ pauseall ; 
 scalar_t__ pausefst ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
ttypause(int pagecnt)
{
	int pch;
	FILE *ttyfp;

	if ((pauseall || (pausefst && pagecnt == 1)) &&
	    isatty(STDOUT_FILENO)) {
		if ((ttyfp = fopen("/dev/tty", "r")) != NULL) {
			(void)putc('\a', stderr);
			while ((pch = getc(ttyfp)) != '\n' && pch != EOF)
				;
			(void)fclose(ttyfp);
		}
	}
}