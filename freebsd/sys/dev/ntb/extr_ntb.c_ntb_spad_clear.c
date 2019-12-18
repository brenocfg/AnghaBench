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
struct ntb_child {unsigned int spadcnt; scalar_t__ spadoff; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  NTB_SPAD_WRITE (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ntb_child* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

void
ntb_spad_clear(device_t ntb)
{
	struct ntb_child *nc = device_get_ivars(ntb);
	unsigned i;

	for (i = 0; i < nc->spadcnt; i++)
		NTB_SPAD_WRITE(device_get_parent(ntb), i + nc->spadoff, 0);
}