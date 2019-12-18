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
struct msgreg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct msgreg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct msgreg*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  msgreg ; 
 int /*<<< orphan*/  msgreg_list ; 

void
ng_unregister_cookie(void *dd)
{
	struct msgreg *d = dd;

	SLIST_REMOVE(&msgreg_list, d, msgreg, link);
	free(d);
}