#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int i; } ;
struct TYPE_8__ {TYPE_3__ v; } ;
struct TYPE_7__ {TYPE_2__ c; } ;
struct TYPE_10__ {int /*<<< orphan*/  op; TYPE_1__ u; struct TYPE_10__** syms; } ;
typedef  TYPE_4__* Node ;

/* Variables and functions */
 scalar_t__ ARG ; 
 scalar_t__ CALL ; 
 int argoffset ; 
 int /*<<< orphan*/  assert (TYPE_4__*) ; 
 scalar_t__ generic (int /*<<< orphan*/ ) ; 
 int maxargoffset ; 

__attribute__((used)) static void gen02(Node p) {
	assert(p);
	if (generic(p->op) == ARG) {
		assert(p->syms[0]);
		argoffset += (p->syms[0]->u.c.v.i < 4 ? 4 : p->syms[0]->u.c.v.i);
	} else if (generic(p->op) == CALL) {
		maxargoffset = (argoffset > maxargoffset ? argoffset : maxargoffset);
		argoffset = 0;
	}
}