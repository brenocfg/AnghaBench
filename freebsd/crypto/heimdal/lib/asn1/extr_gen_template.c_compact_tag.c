#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; struct TYPE_4__* subtype; } ;
typedef  TYPE_1__ Type ;

/* Variables and functions */
 scalar_t__ TTag ; 

__attribute__((used)) static const Type *
compact_tag(const Type *t)
{
    while (t->type == TTag)
	t = t->subtype;
    return t;
}