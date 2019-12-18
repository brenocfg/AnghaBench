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
struct trapframe {int /*<<< orphan*/  tf_sstatus; int /*<<< orphan*/  tf_sepc; int /*<<< orphan*/ * tf_a; int /*<<< orphan*/ * tf_s; int /*<<< orphan*/ * tf_t; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void
dump_regs(struct trapframe *frame)
{
	int n;
	int i;

	n = (sizeof(frame->tf_t) / sizeof(frame->tf_t[0]));
	for (i = 0; i < n; i++)
		printf("t[%d] == 0x%016lx\n", i, frame->tf_t[i]);

	n = (sizeof(frame->tf_s) / sizeof(frame->tf_s[0]));
	for (i = 0; i < n; i++)
		printf("s[%d] == 0x%016lx\n", i, frame->tf_s[i]);

	n = (sizeof(frame->tf_a) / sizeof(frame->tf_a[0]));
	for (i = 0; i < n; i++)
		printf("a[%d] == 0x%016lx\n", i, frame->tf_a[i]);

	printf("sepc == 0x%016lx\n", frame->tf_sepc);
	printf("sstatus == 0x%016lx\n", frame->tf_sstatus);
}