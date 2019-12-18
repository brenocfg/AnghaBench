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
typedef  int /*<<< orphan*/  uint32_t ;
struct ntb_child {scalar_t__ spadoff; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int NTB_PEER_SPAD_WRITE (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ntb_child* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

int
ntb_peer_spad_write(device_t ntb, unsigned int idx, uint32_t val)
{
	struct ntb_child *nc = device_get_ivars(ntb);

	return (NTB_PEER_SPAD_WRITE(device_get_parent(ntb), idx + nc->spadoff,
	    val));
}