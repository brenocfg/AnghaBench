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
typedef  int u8 ;
struct mce {int status; int /*<<< orphan*/  bank; } ;
struct cpuinfo_x86 {int x86; int x86_model; } ;
typedef  enum smca_bank_types { ____Placeholder_smca_bank_types } smca_bank_types ;

/* Variables and functions */
 int SMCA_IF ; 
 struct cpuinfo_x86 boot_cpu_data ; 
 int smca_get_bank_type (int /*<<< orphan*/ ) ; 

bool amd_filter_mce(struct mce *m)
{
	enum smca_bank_types bank_type = smca_get_bank_type(m->bank);
	struct cpuinfo_x86 *c = &boot_cpu_data;
	u8 xec = (m->status >> 16) & 0x3F;

	/* See Family 17h Models 10h-2Fh Erratum #1114. */
	if (c->x86 == 0x17 &&
	    c->x86_model >= 0x10 && c->x86_model <= 0x2F &&
	    bank_type == SMCA_IF && xec == 10)
		return true;

	return false;
}