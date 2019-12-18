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
struct TYPE_2__ {int code; } ;
struct block {struct block* head; TYPE_1__ s; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;

/* Variables and functions */
 scalar_t__ newchunk (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline struct block *
new_block(compiler_state_t *cstate, int code)
{
	struct block *p;

	p = (struct block *)newchunk(cstate, sizeof(*p));
	p->s.code = code;
	p->head = p;

	return p;
}