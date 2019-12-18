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
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_VXLAN ; 
 int M_ZERO ; 
 struct vxlan_ftable_entry* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct vxlan_ftable_entry *
vxlan_ftable_entry_alloc(void)
{
	struct vxlan_ftable_entry *fe;

	fe = malloc(sizeof(*fe), M_VXLAN, M_ZERO | M_NOWAIT);

	return (fe);
}