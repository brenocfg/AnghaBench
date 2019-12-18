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
struct datareg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct datareg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  datareg ; 
 int /*<<< orphan*/  datareg_list ; 
 int /*<<< orphan*/  free (struct datareg*) ; 
 int /*<<< orphan*/  link ; 

void
ng_unregister_hook(void *dd)
{
	struct datareg *d = dd;

	SLIST_REMOVE(&datareg_list, d, datareg, link);
	free(d);
}