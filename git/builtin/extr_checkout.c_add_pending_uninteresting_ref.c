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
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNINTERESTING ; 
 int /*<<< orphan*/  add_pending_oid (void*,char const*,struct object_id const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_pending_uninteresting_ref(const char *refname,
					 const struct object_id *oid,
					 int flags, void *cb_data)
{
	add_pending_oid(cb_data, refname, oid, UNINTERESTING);
	return 0;
}