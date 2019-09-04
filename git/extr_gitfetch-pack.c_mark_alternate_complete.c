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
struct object {int /*<<< orphan*/  oid; } ;
struct fetch_negotiator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mark_complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mark_alternate_complete(struct fetch_negotiator *unused,
				    struct object *obj)
{
	mark_complete(&obj->oid);
}