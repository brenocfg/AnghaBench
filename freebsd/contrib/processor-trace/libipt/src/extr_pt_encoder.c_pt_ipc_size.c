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
 int pt_pl_ip_full_size ; 
 int pt_pl_ip_sext48_size ; 
 int pt_pl_ip_upd16_size ; 
 int pt_pl_ip_upd32_size ; 
 int pt_pl_ip_upd48_size ; 
 int pte_invalid ; 

__attribute__((used)) static int pt_ipc_size(enum pt_ip_compression ipc)
{
	switch (ipc) {
	case pt_ipc_suppressed:
		return 0;

	case pt_ipc_update_16:
		return pt_pl_ip_upd16_size;

	case pt_ipc_update_32:
		return pt_pl_ip_upd32_size;

	case pt_ipc_update_48:
		return pt_pl_ip_upd48_size;

	case pt_ipc_sext_48:
		return pt_pl_ip_sext48_size;

	case pt_ipc_full:
		return pt_pl_ip_full_size;
	}

	return -pte_invalid;
}