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
struct ref_store {int dummy; } ;
struct object_id {int dummy; } ;
typedef  int (* each_ref_fn ) (char*,struct object_id*,int,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 int /*<<< orphan*/  refs_read_ref_full (struct ref_store*,char*,int /*<<< orphan*/ ,struct object_id*,int*) ; 

int refs_head_ref(struct ref_store *refs, each_ref_fn fn, void *cb_data)
{
	struct object_id oid;
	int flag;

	if (!refs_read_ref_full(refs, "HEAD", RESOLVE_REF_READING,
				&oid, &flag))
		return fn("HEAD", &oid, flag, cb_data);

	return 0;
}