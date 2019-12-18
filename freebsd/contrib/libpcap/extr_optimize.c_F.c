#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct valnode {int code; int v0; int v1; int val; struct valnode* next; } ;
struct TYPE_5__ {int curval; struct valnode** hashtbl; int /*<<< orphan*/  next_vnode; TYPE_1__* vmap; } ;
typedef  TYPE_2__ opt_state_t ;
struct TYPE_4__ {int const_val; int is_const; } ;

/* Variables and functions */
 scalar_t__ BPF_CLASS (int) ; 
 scalar_t__ BPF_IMM ; 
 scalar_t__ BPF_LD ; 
 scalar_t__ BPF_LDX ; 
 scalar_t__ BPF_MODE (int) ; 
 int MODULUS ; 

__attribute__((used)) static int
F(opt_state_t *opt_state, int code, int v0, int v1)
{
	u_int hash;
	int val;
	struct valnode *p;

	hash = (u_int)code ^ (v0 << 4) ^ (v1 << 8);
	hash %= MODULUS;

	for (p = opt_state->hashtbl[hash]; p; p = p->next)
		if (p->code == code && p->v0 == v0 && p->v1 == v1)
			return p->val;

	val = ++opt_state->curval;
	if (BPF_MODE(code) == BPF_IMM &&
	    (BPF_CLASS(code) == BPF_LD || BPF_CLASS(code) == BPF_LDX)) {
		opt_state->vmap[val].const_val = v0;
		opt_state->vmap[val].is_const = 1;
	}
	p = opt_state->next_vnode++;
	p->val = val;
	p->code = code;
	p->v0 = v0;
	p->v1 = v1;
	p->next = opt_state->hashtbl[hash];
	opt_state->hashtbl[hash] = p;

	return val;
}