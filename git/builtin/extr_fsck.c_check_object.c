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
struct object {int flags; } ;

/* Variables and functions */
 int REACHABLE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  check_reachable_object (struct object*) ; 
 int /*<<< orphan*/  check_unreachable_object (struct object*) ; 
 int /*<<< orphan*/  describe_object (struct object*) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void check_object(struct object *obj)
{
	if (verbose)
		fprintf_ln(stderr, _("Checking %s"), describe_object(obj));

	if (obj->flags & REACHABLE)
		check_reachable_object(obj);
	else
		check_unreachable_object(obj);
}