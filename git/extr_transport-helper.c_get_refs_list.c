#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct transport {TYPE_1__* vtable; } ;
struct ref {int dummy; } ;
struct argv_array {int dummy; } ;
struct TYPE_2__ {struct ref* (* get_refs_list ) (struct transport*,int,struct argv_array const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  do_take_over (struct transport*) ; 
 int /*<<< orphan*/  get_helper (struct transport*) ; 
 struct ref* get_refs_list_using_list (struct transport*,int) ; 
 scalar_t__ process_connect (struct transport*,int) ; 
 struct ref* stub1 (struct transport*,int,struct argv_array const*) ; 

__attribute__((used)) static struct ref *get_refs_list(struct transport *transport, int for_push,
				 const struct argv_array *ref_prefixes)
{
	get_helper(transport);

	if (process_connect(transport, for_push)) {
		do_take_over(transport);
		return transport->vtable->get_refs_list(transport, for_push, ref_prefixes);
	}

	return get_refs_list_using_list(transport, for_push);
}