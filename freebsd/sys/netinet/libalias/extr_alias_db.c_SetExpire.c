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
struct alias_link {int expire_time; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLink (struct alias_link*) ; 
 int /*<<< orphan*/  LINK_PERMANENT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

void
SetExpire(struct alias_link *lnk, int expire)
{
	if (expire == 0) {
		lnk->flags &= ~LINK_PERMANENT;
		DeleteLink(lnk);
	} else if (expire == -1) {
		lnk->flags |= LINK_PERMANENT;
	} else if (expire > 0) {
		lnk->expire_time = expire;
	} else {
#ifdef LIBALIAS_DEBUG
		fprintf(stderr, "PacketAlias/SetExpire(): ");
		fprintf(stderr, "error in expire parameter\n");
#endif
	}
}