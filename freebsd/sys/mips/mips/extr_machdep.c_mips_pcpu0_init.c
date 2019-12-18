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
struct pcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCPU_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  pcpu_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  thread0 ; 

void
mips_pcpu0_init()
{
	/* Initialize pcpu info of cpu-zero */
	pcpu_init(PCPU_ADDR(0), 0, sizeof(struct pcpu));
	PCPU_SET(curthread, &thread0);
}