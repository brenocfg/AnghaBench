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
typedef  int /*<<< orphan*/  u_int ;
struct trapframe {int dummy; } ;
struct thread {int dummy; } ;
struct ksig {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort_fatal (struct trapframe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*,struct ksig*) ; 

__attribute__((used)) static int
abort_icache(struct trapframe *tf, u_int idx, u_int fsr, u_int far,
    u_int prefetch, struct thread *td, struct ksig *ksig)
{

	abort_fatal(tf, idx, fsr, far, prefetch, td, ksig);
	return(0);
}