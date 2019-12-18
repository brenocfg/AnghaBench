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
struct trapframe {int tf_esp; } ;

/* Variables and functions */
 scalar_t__ TF_HAS_STACKREGS (struct trapframe*) ; 

__attribute__((used)) static __inline int
get_esp(struct trapframe *tf)
{
	return (TF_HAS_STACKREGS(tf) ? tf->tf_esp : (intptr_t)&tf->tf_esp);
}