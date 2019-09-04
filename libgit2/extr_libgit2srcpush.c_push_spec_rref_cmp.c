#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dst; } ;
struct TYPE_4__ {TYPE_1__ refspec; } ;
typedef  TYPE_2__ push_spec ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int push_spec_rref_cmp(const void *a, const void *b)
{
	const push_spec *push_spec_a = a, *push_spec_b = b;

	return strcmp(push_spec_a->refspec.dst, push_spec_b->refspec.dst);
}