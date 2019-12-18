#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct attr_check {int /*<<< orphan*/  nr; int /*<<< orphan*/  items; int /*<<< orphan*/  alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COPY_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct attr_check* attr_check_alloc () ; 

struct attr_check *attr_check_dup(const struct attr_check *check)
{
	struct attr_check *ret;

	if (!check)
		return NULL;

	ret = attr_check_alloc();

	ret->nr = check->nr;
	ret->alloc = check->alloc;
	ALLOC_ARRAY(ret->items, ret->nr);
	COPY_ARRAY(ret->items, check->items, ret->nr);

	return ret;
}