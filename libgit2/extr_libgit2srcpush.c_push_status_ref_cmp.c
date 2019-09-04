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
struct TYPE_2__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ push_status ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int push_status_ref_cmp(const void *a, const void *b)
{
	const push_status *push_status_a = a, *push_status_b = b;

	return strcmp(push_status_a->ref, push_status_b->ref);
}