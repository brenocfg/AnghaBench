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
 int /*<<< orphan*/  null_oid ; 
 int oideq (struct object_id const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int is_null_oid(const struct object_id *oid)
{
	return oideq(oid, &null_oid);
}