#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Type ;
struct TYPE_5__ {int op; struct TYPE_5__* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEW0 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STMT ; 

__attribute__((used)) static Type tnode(int op, Type type) {
	Type ty;

	NEW0(ty, STMT);
	ty->op = op;
	ty->type = type;
	return ty;
}