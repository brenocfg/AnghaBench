#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* Tree ;
struct TYPE_6__ {TYPE_1__* sym; } ;
struct TYPE_7__ {TYPE_2__ u; int /*<<< orphan*/  op; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ isaddrop (int /*<<< orphan*/ ) ; 
 char* stringf (char*,int /*<<< orphan*/ ) ; 

char *funcname(Tree f) {
	if (isaddrop(f->op))
		return stringf("`%s'", f->u.sym->name);
	return "a function";
}