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
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct do_for_each_ref_help {int (* fn ) (char const*,struct object_id const*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  cb_data; } ;

/* Variables and functions */
 int stub1 (char const*,struct object_id const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_for_each_ref_helper(struct repository *r,
				  const char *refname,
				  const struct object_id *oid,
				  int flags,
				  void *cb_data)
{
	struct do_for_each_ref_help *hp = cb_data;

	return hp->fn(refname, oid, flags, hp->cb_data);
}