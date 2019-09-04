#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Tree ;
struct TYPE_9__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond (TYPE_1__*) ; 
 int /*<<< orphan*/  inttype ; 
 int /*<<< orphan*/  isscalar (int /*<<< orphan*/ ) ; 
 TYPE_1__* simplify (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typeerror (int,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static Tree andtree(int op, Tree l, Tree r) {
	if (!isscalar(l->type) || !isscalar(r->type))
		typeerror(op, l, r);
	return simplify(op, inttype, cond(l), cond(r));
}