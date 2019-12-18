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
struct TYPE_2__ {scalar_t__ k; } ;
struct slist {TYPE_1__ s; } ;
struct arth {int /*<<< orphan*/  s; scalar_t__ regno; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;

/* Variables and functions */
 int BPF_ALU ; 
 int BPF_NEG ; 
 int BPF_ST ; 
 struct slist* new_stmt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sappend (int /*<<< orphan*/ ,struct slist*) ; 
 struct slist* xfer_to_a (int /*<<< orphan*/ *,struct arth*) ; 

struct arth *
gen_neg(compiler_state_t *cstate, struct arth *a)
{
	struct slist *s;

	s = xfer_to_a(cstate, a);
	sappend(a->s, s);
	s = new_stmt(cstate, BPF_ALU|BPF_NEG);
	s->s.k = 0;
	sappend(a->s, s);
	s = new_stmt(cstate, BPF_ST);
	s->s.k = a->regno;
	sappend(a->s, s);

	return a;
}