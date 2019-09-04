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
struct stream_filter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * vtbl; } ;
struct cascade_filter {TYPE_1__ filter; scalar_t__ ptr; scalar_t__ end; struct stream_filter* two; struct stream_filter* one; } ;

/* Variables and functions */
 int /*<<< orphan*/  cascade_vtbl ; 
 scalar_t__ is_null_stream_filter (struct stream_filter*) ; 
 struct cascade_filter* xmalloc (int) ; 

__attribute__((used)) static struct stream_filter *cascade_filter(struct stream_filter *one,
					    struct stream_filter *two)
{
	struct cascade_filter *cascade;

	if (!one || is_null_stream_filter(one))
		return two;
	if (!two || is_null_stream_filter(two))
		return one;

	cascade = xmalloc(sizeof(*cascade));
	cascade->one = one;
	cascade->two = two;
	cascade->end = cascade->ptr = 0;
	cascade->filter.vtbl = &cascade_vtbl;
	return (struct stream_filter *)cascade;
}