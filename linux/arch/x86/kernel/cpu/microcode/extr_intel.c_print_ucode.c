#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ucode_cpu_info {struct microcode_intel* mc; } ;
struct TYPE_2__ {int /*<<< orphan*/  date; } ;
struct microcode_intel {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_ucode_info (struct ucode_cpu_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void print_ucode(struct ucode_cpu_info *uci)
{
	struct microcode_intel *mc;

	mc = uci->mc;
	if (!mc)
		return;

	print_ucode_info(uci, mc->hdr.date);
}