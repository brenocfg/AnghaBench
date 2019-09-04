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
 scalar_t__ is_null_oid (struct object_id const*) ; 

__attribute__((used)) static struct object_id *stage_oid(const struct object_id *oid, unsigned mode)
{
	return (is_null_oid(oid) || mode == 0) ? NULL: (struct object_id *)oid;
}