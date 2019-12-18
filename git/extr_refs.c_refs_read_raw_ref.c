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
struct strbuf {int dummy; } ;
struct ref_store {TYPE_1__* be; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {int (* read_raw_ref ) (struct ref_store*,char const*,struct object_id*,struct strbuf*,unsigned int*) ;} ;

/* Variables and functions */
 int stub1 (struct ref_store*,char const*,struct object_id*,struct strbuf*,unsigned int*) ; 

int refs_read_raw_ref(struct ref_store *ref_store,
		      const char *refname, struct object_id *oid,
		      struct strbuf *referent, unsigned int *type)
{
	return ref_store->be->read_raw_ref(ref_store, refname, oid, referent, type);
}