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
struct range_set {int /*<<< orphan*/  nr; int /*<<< orphan*/  ranges; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_set_init (struct range_set*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void range_set_copy(struct range_set *dst, struct range_set *src)
{
	range_set_init(dst, src->nr);
	COPY_ARRAY(dst->ranges, src->ranges, src->nr);
	dst->nr = src->nr;
}