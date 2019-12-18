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
struct mac_mls {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  destroyed_not_inited ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct mac_mls*) ; 
 int /*<<< orphan*/  zone_mls ; 

__attribute__((used)) static void
mls_free(struct mac_mls *mm)
{

	if (mm != NULL)
		uma_zfree(zone_mls, mm);
	else
		atomic_add_int(&destroyed_not_inited, 1);
}