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
struct bpf_d {int /*<<< orphan*/ * bd_label; } ;

/* Variables and functions */
 int MPC_OBJECT_BPFDESC ; 
 int /*<<< orphan*/ * mac_bpfdesc_label_alloc () ; 
 int mac_labeled ; 

void
mac_bpfdesc_init(struct bpf_d *d)
{

	if (mac_labeled & MPC_OBJECT_BPFDESC)
		d->bd_label = mac_bpfdesc_label_alloc();
	else
		d->bd_label = NULL;
}