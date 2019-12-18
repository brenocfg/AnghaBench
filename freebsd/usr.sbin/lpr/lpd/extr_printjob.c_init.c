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
struct printer {int /*<<< orphan*/  page_plength; int /*<<< orphan*/  page_pwidth; int /*<<< orphan*/  page_length; int /*<<< orphan*/  page_width; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 char* checkremote (struct printer*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * length ; 
 int /*<<< orphan*/ * pxlength ; 
 int /*<<< orphan*/ * pxwidth ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * width ; 

__attribute__((used)) static void
init(struct printer *pp)
{
	char *s;

	sprintf(&width[2], "%ld", pp->page_width);
	sprintf(&length[2], "%ld", pp->page_length);
	sprintf(&pxwidth[2], "%ld", pp->page_pwidth);
	sprintf(&pxlength[2], "%ld", pp->page_plength);
	if ((s = checkremote(pp)) != NULL) {
		syslog(LOG_WARNING, "%s", s);
		free(s);
	}
}