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
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  oidcpy (struct object_id*,struct object_id const*) ; 
 struct object_id* xmalloc (int) ; 

__attribute__((used)) static inline struct object_id *oiddup(const struct object_id *src)
{
	struct object_id *dst = xmalloc(sizeof(struct object_id));
	oidcpy(dst, src);
	return dst;
}