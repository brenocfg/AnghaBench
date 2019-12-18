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
typedef  void* jmp_buf ;

/* Variables and functions */
 int /*<<< orphan*/  db_trace_self () ; 
 void* kdb_jmpbuf (void*) ; 
 scalar_t__ setjmp (void*) ; 

__attribute__((used)) static void
db_trace_self_wrapper(void)
{
	jmp_buf jb;
	void *prev_jb;

	prev_jb = kdb_jmpbuf(jb);
	if (setjmp(jb) == 0)
		db_trace_self();
	(void)kdb_jmpbuf(prev_jb);
}