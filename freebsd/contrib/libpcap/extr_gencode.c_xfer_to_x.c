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
struct TYPE_2__ {int /*<<< orphan*/  k; } ;
struct slist {TYPE_1__ s; } ;
struct arth {int /*<<< orphan*/  regno; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;

/* Variables and functions */
 int BPF_LDX ; 
 int BPF_MEM ; 
 struct slist* new_stmt (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct slist *
xfer_to_x(compiler_state_t *cstate, struct arth *a)
{
	struct slist *s;

	s = new_stmt(cstate, BPF_LDX|BPF_MEM);
	s->s.k = a->regno;
	return s;
}