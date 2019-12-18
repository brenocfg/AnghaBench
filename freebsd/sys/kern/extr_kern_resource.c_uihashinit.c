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
 int /*<<< orphan*/  M_UIDINFO ; 
 int /*<<< orphan*/  hashinit (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int maxproc ; 
 int /*<<< orphan*/  rw_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  uihash ; 
 int /*<<< orphan*/  uihashtbl ; 
 int /*<<< orphan*/  uihashtbl_lock ; 

void
uihashinit()
{

	uihashtbl = hashinit(maxproc / 16, M_UIDINFO, &uihash);
	rw_init(&uihashtbl_lock, "uidinfo hash");
}