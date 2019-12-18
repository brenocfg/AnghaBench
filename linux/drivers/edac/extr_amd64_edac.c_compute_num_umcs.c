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
typedef  int u8 ;
struct TYPE_2__ {int x86_model; int x86; } ;

/* Variables and functions */
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  edac_dbg (int,char*,int) ; 
 int num_umcs ; 

__attribute__((used)) static void compute_num_umcs(void)
{
	u8 model = boot_cpu_data.x86_model;

	if (boot_cpu_data.x86 < 0x17)
		return;

	if (model >= 0x30 && model <= 0x3f)
		num_umcs = 8;
	else
		num_umcs = 2;

	edac_dbg(1, "Number of UMCs: %x", num_umcs);
}