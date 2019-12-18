#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct roff_man {TYPE_1__* last; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANDOCERR_FI_TAB ; 
 int NODE_NOFILL ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void
check_text(struct roff_man *mdoc, int ln, int pos, char *p)
{
	char		*cp;

	if (mdoc->last->flags & NODE_NOFILL)
		return;

	for (cp = p; NULL != (p = strchr(p, '\t')); p++)
		mandoc_msg(MANDOCERR_FI_TAB, ln, pos + (int)(p - cp), NULL);
}