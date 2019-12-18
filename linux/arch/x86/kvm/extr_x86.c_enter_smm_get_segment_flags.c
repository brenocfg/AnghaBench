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
typedef  int u32 ;
struct kvm_segment {int g; int db; int l; int avl; int present; int dpl; int s; int type; } ;

/* Variables and functions */

__attribute__((used)) static u32 enter_smm_get_segment_flags(struct kvm_segment *seg)
{
	u32 flags = 0;
	flags |= seg->g       << 23;
	flags |= seg->db      << 22;
	flags |= seg->l       << 21;
	flags |= seg->avl     << 20;
	flags |= seg->present << 15;
	flags |= seg->dpl     << 13;
	flags |= seg->s       << 12;
	flags |= seg->type    << 8;
	return flags;
}