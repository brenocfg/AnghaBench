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
 int oidcmp (struct object_id const*,struct object_id const*) ; 

__attribute__((used)) static int oid_compare(const void *_a, const void *_b)
{
	const struct object_id *a = (const struct object_id *)_a;
	const struct object_id *b = (const struct object_id *)_b;
	return oidcmp(a, b);
}