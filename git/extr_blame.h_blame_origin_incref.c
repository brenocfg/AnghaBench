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
struct blame_origin {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */

__attribute__((used)) static inline struct blame_origin *blame_origin_incref(struct blame_origin *o)
{
	if (o)
		o->refcnt++;
	return o;
}