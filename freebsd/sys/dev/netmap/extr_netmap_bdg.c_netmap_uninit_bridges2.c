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
typedef  int u_int ;
struct nm_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDG_RWDESTROY (struct nm_bridge*) ; 
 int /*<<< orphan*/  nm_os_free (struct nm_bridge*) ; 

void
netmap_uninit_bridges2(struct nm_bridge *b, u_int n)
{
	int i;

	if (b == NULL)
		return;

	for (i = 0; i < n; i++)
		BDG_RWDESTROY(&b[i]);
	nm_os_free(b);
}