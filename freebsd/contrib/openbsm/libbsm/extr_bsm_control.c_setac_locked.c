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
typedef  scalar_t__ time_t ;
struct stat {scalar_t__ st_ctime; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fp ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int ptrmoved ; 

__attribute__((used)) static void
setac_locked(void)
{
	static time_t lastctime = 0;
	struct stat sbuf;

	ptrmoved = 1;
	if (fp != NULL) {
		/*
		 * Check to see if the file on disk has changed.  If so,
		 * force a re-read of the file by closing it.
		 */
		if (fstat(fileno(fp), &sbuf) < 0)
			goto closefp;
		if (lastctime != sbuf.st_ctime) {
			lastctime = sbuf.st_ctime;
closefp:
			fclose(fp);
			fp = NULL;
			return;
		}

		fseek(fp, 0, SEEK_SET);
	}
}