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

/* Variables and functions */
 int /*<<< orphan*/  closemt () ; 
 char* dirfile ; 
 int /*<<< orphan*/  exit (int) ; 
 char* modefile ; 
 int /*<<< orphan*/  truncate (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 

void
done(int exitcode)
{

	closemt();
	if (modefile[0] != '#') {
		(void) truncate(modefile, 0);
		(void) unlink(modefile);
	}
	if (dirfile[0] != '#') {
		(void) truncate(dirfile, 0);
		(void) unlink(dirfile);
	}
	exit(exitcode);
}