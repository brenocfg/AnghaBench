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
struct source {int dummy; } ;
struct TYPE_2__ {size_t readsp; int readstack_sz; struct source* readstack; } ;

/* Variables and functions */
 int EOF ; 
 TYPE_1__ bmachine ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int readch () ; 
 struct source* reallocarray (struct source*,size_t,int) ; 
 int /*<<< orphan*/  src_free () ; 
 int /*<<< orphan*/  src_setstring (struct source*,char*) ; 
 int /*<<< orphan*/  unreadch () ; 

__attribute__((used)) static void
eval_string(char *p)
{
	int ch;

	if (bmachine.readsp > 0) {
		/* Check for tail call. Do not recurse in that case. */
		ch = readch();
		if (ch == EOF) {
			src_free();
			src_setstring(&bmachine.readstack[bmachine.readsp], p);
			return;
		} else
			unreadch();
	}
	if (bmachine.readsp == bmachine.readstack_sz - 1) {
		size_t newsz = bmachine.readstack_sz * 2;
		struct source *stack;
		stack = reallocarray(bmachine.readstack, newsz,
		    sizeof(struct source));
		if (stack == NULL)
			err(1, "recursion too deep");
		bmachine.readstack_sz = newsz;
		bmachine.readstack = stack;
	}
	src_setstring(&bmachine.readstack[++bmachine.readsp], p);
}