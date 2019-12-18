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
typedef  enum pt_ip_compression { ____Placeholder_pt_ip_compression } pt_ip_compression ;

/* Variables and functions */
#define  pt_ipc_full 133 
#define  pt_ipc_sext_48 132 
#define  pt_ipc_suppressed 131 
#define  pt_ipc_update_16 130 
#define  pt_ipc_update_32 129 
#define  pt_ipc_update_48 128 
 int pte_bad_packet ; 

__attribute__((used)) static int pt_pkt_ip_size(enum pt_ip_compression ipc)
{
	switch (ipc) {
	case pt_ipc_suppressed:
		return 0;

	case pt_ipc_update_16:
		return 2;

	case pt_ipc_update_32:
		return 4;

	case pt_ipc_update_48:
	case pt_ipc_sext_48:
		return 6;

	case pt_ipc_full:
		return 8;
	}

	return -pte_bad_packet;
}