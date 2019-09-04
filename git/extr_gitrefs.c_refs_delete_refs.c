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
struct string_list {int dummy; } ;
struct ref_store {TYPE_1__* be; } ;
struct TYPE_2__ {int (* delete_refs ) (struct ref_store*,char const*,struct string_list*,unsigned int) ;} ;

/* Variables and functions */
 int stub1 (struct ref_store*,char const*,struct string_list*,unsigned int) ; 

int refs_delete_refs(struct ref_store *refs, const char *msg,
		     struct string_list *refnames, unsigned int flags)
{
	return refs->be->delete_refs(refs, msg, refnames, flags);
}