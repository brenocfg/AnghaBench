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
struct vxlan_ftable_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_VXLAN ; 
 int /*<<< orphan*/  free (struct vxlan_ftable_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vxlan_ftable_entry_free(struct vxlan_ftable_entry *fe)
{

	free(fe, M_VXLAN);
}