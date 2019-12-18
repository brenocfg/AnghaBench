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

/* Variables and functions */
 int /*<<< orphan*/  CC_C ; 
 int /*<<< orphan*/  exec_opb (long,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_opl (long,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_opq (long,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_opw (long,long,int /*<<< orphan*/ ) ; 
 long i2l (long) ; 

void exec_op(long s0, long s1)
{
    s0 = i2l(s0);
    s1 = i2l(s1);
#if defined(__x86_64__)
    exec_opq(s0, s1, 0);
#endif
    exec_opl(s0, s1, 0);
    exec_opw(s0, s1, 0);
    exec_opb(s0, s1, 0);
#ifdef OP_CC
#if defined(__x86_64__)
    exec_opq(s0, s1, CC_C);
#endif
    exec_opl(s0, s1, CC_C);
    exec_opw(s0, s1, CC_C);
    exec_opb(s0, s1, CC_C);
#endif
}