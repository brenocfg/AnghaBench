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
struct rev_info {int dummy; } ;
struct object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IFINVALID ; 
 int /*<<< orphan*/  add_pending_object_with_mode (struct rev_info*,struct object*,char const*,int /*<<< orphan*/ ) ; 

void add_pending_object(struct rev_info *revs,
			struct object *obj, const char *name)
{
	add_pending_object_with_mode(revs, obj, name, S_IFINVALID);
}