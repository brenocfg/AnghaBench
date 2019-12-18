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
struct TYPE_3__ {int /*<<< orphan*/  slb; } ;
struct pcpu {TYPE_1__ pc_aim; } ;
struct TYPE_4__ {int /*<<< orphan*/  slb; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 TYPE_2__ aim ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
cpu_pcpu_init(struct pcpu *pcpu, int cpuid, size_t sz)
{
#ifdef __powerpc64__
/* Copy the SLB contents from the current CPU */
memcpy(pcpu->pc_aim.slb, PCPU_GET(aim.slb), sizeof(pcpu->pc_aim.slb));
#endif
}