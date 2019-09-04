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
struct tracking_name_data {int /*<<< orphan*/  dst_ref; struct object_id* default_dst_oid; int /*<<< orphan*/  dst_oid; int /*<<< orphan*/  default_dst_ref; scalar_t__ default_remote; int /*<<< orphan*/  num_matches; int /*<<< orphan*/  src_ref; } ;
struct remote {int /*<<< orphan*/  name; } ;
struct refspec_item {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ get_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct refspec_item*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,int /*<<< orphan*/ ) ; 
 scalar_t__ remote_find_tracking (struct remote*,struct refspec_item*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,scalar_t__) ; 
 struct object_id* xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_tracking_name(struct remote *remote, void *cb_data)
{
	struct tracking_name_data *cb = cb_data;
	struct refspec_item query;
	memset(&query, 0, sizeof(struct refspec_item));
	query.src = cb->src_ref;
	if (remote_find_tracking(remote, &query) ||
	    get_oid(query.dst, cb->dst_oid)) {
		free(query.dst);
		return 0;
	}
	cb->num_matches++;
	if (cb->default_remote && !strcmp(remote->name, cb->default_remote)) {
		struct object_id *dst = xmalloc(sizeof(*cb->default_dst_oid));
		cb->default_dst_ref = xstrdup(query.dst);
		oidcpy(dst, cb->dst_oid);
		cb->default_dst_oid = dst;
	}
	if (cb->dst_ref) {
		free(query.dst);
		return 0;
	}
	cb->dst_ref = query.dst;
	return 0;
}