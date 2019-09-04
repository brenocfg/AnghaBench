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
 int ALLOW_REACHABLE_SHA1 ; 
 int ALLOW_TIP_SHA1 ; 
 int HIDDEN_REF ; 
 int OUR_REF ; 
 int allow_unadvertised_object_request ; 

__attribute__((used)) static int is_our_ref(struct object *o)
{
	int allow_hidden_ref = (allow_unadvertised_object_request &
			(ALLOW_TIP_SHA1 | ALLOW_REACHABLE_SHA1));
	return o->flags & ((allow_hidden_ref ? HIDDEN_REF : 0) | OUR_REF);
}