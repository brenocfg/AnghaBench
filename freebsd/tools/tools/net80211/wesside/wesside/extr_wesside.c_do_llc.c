#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int control; int /*<<< orphan*/  ether_type; } ;
struct TYPE_4__ {TYPE_1__ type_snap; } ;
struct llc {TYPE_2__ llc_un; void* llc_ssap; void* llc_dsap; } ;

/* Variables and functions */
 void* LLC_SNAP_LSAP ; 
 int /*<<< orphan*/  htons (unsigned short) ; 
 int /*<<< orphan*/  memset (struct llc*,int /*<<< orphan*/ ,int) ; 

void do_llc(unsigned char* buf, unsigned short type) {
	struct llc* h = (struct llc*) buf;

	memset(h, 0, sizeof(*h));
	h->llc_dsap = LLC_SNAP_LSAP;
	h->llc_ssap = LLC_SNAP_LSAP;
	h->llc_un.type_snap.control = 3;
	h->llc_un.type_snap.ether_type = htons(type);
}