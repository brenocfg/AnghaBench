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
typedef  union vfpf_tlvs {int dummy; } vfpf_tlvs ;
typedef  int u32 ;
struct vfpf_first_tlv {int dummy; } ;

/* Variables and functions */

bool ecore_iov_is_valid_vfpf_msg_length(u32 length)
{
	return (length >= sizeof(struct vfpf_first_tlv) &&
		(length <= sizeof(union vfpf_tlvs)));
}