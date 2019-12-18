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
struct oid {int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ ) ; 
 scalar_t__ sysctlnametomib (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
oid_get_by_name(struct oid *o, const char *name)
{

	o->len = nitems(o->id);
	if (sysctlnametomib(name, o->id, &o->len) != 0)
		err(1, "sysctl(%s)", name);
}