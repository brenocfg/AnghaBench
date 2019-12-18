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
typedef  int /*<<< orphan*/  time_t ;
struct printer {int tof; char* form_feed; int /*<<< orphan*/  no_formfeed; scalar_t__ short_banner; } ;

/* Variables and functions */
 char* class ; 
 char* ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofd ; 
 int /*<<< orphan*/  scan_out (struct printer*,int /*<<< orphan*/ ,char*,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
banner(struct printer *pp, char *name1, char *name2)
{
	time_t tvec;

	time(&tvec);
	if (!pp->no_formfeed && !pp->tof)
		(void) write(ofd, pp->form_feed, strlen(pp->form_feed));
	if (pp->short_banner) {	/* short banner only */
		if (class[0]) {
			(void) write(ofd, class, strlen(class));
			(void) write(ofd, ":", 1);
		}
		(void) write(ofd, name1, strlen(name1));
		(void) write(ofd, "  Job: ", 7);
		(void) write(ofd, name2, strlen(name2));
		(void) write(ofd, "  Date: ", 8);
		(void) write(ofd, ctime(&tvec), 24);
		(void) write(ofd, "\n", 1);
	} else {	/* normal banner */
		(void) write(ofd, "\n\n\n", 3);
		scan_out(pp, ofd, name1, '\0');
		(void) write(ofd, "\n\n", 2);
		scan_out(pp, ofd, name2, '\0');
		if (class[0]) {
			(void) write(ofd,"\n\n\n",3);
			scan_out(pp, ofd, class, '\0');
		}
		(void) write(ofd, "\n\n\n\n\t\t\t\t\tJob:  ", 15);
		(void) write(ofd, name2, strlen(name2));
		(void) write(ofd, "\n\t\t\t\t\tDate: ", 12);
		(void) write(ofd, ctime(&tvec), 24);
		(void) write(ofd, "\n", 1);
	}
	if (!pp->no_formfeed)
		(void) write(ofd, pp->form_feed, strlen(pp->form_feed));
	pp->tof = 1;
}