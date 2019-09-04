#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* Tree ;
struct TYPE_7__ {int i; } ;
struct TYPE_8__ {TYPE_1__ v; } ;
struct TYPE_10__ {TYPE_2__ u; } ;
struct TYPE_9__ {scalar_t__ op; } ;

/* Variables and functions */
 scalar_t__ CNST ; 
 scalar_t__ I ; 
 scalar_t__ U ; 
 TYPE_5__* cast (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* constexpr (int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  inttype ; 
 int /*<<< orphan*/  needconst ; 

int intexpr(int tok, int n) {
	Tree p = constexpr(tok);

	needconst++;
	if (p->op == CNST+I || p->op == CNST+U)
		n = cast(p, inttype)->u.v.i;
	else
		error("integer expression must be constant\n");
	needconst--;
	return n;
}