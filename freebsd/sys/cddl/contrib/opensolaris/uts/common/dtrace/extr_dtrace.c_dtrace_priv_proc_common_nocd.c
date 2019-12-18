#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int p_flag; } ;
typedef  TYPE_1__ proc_t ;

/* Variables and functions */
 int SNOCD ; 
 int /*<<< orphan*/  curthread ; 
 TYPE_1__* ttoproc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtrace_priv_proc_common_nocd(void)
{
	proc_t *proc;

	if ((proc = ttoproc(curthread)) != NULL &&
	    !(proc->p_flag & SNOCD))
		return (1);

	return (0);
}