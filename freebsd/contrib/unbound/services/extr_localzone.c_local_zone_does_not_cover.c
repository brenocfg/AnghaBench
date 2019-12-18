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
struct query_info {int /*<<< orphan*/  qtype; int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct local_zone {scalar_t__ type; int /*<<< orphan*/  data; } ;
struct local_rrset {int dummy; } ;
struct TYPE_2__ {struct local_data* key; } ;
struct local_data {int namelabs; TYPE_1__ node; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct local_rrset* local_data_find_type (struct local_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ local_zone_always_transparent ; 
 scalar_t__ local_zone_inform ; 
 scalar_t__ local_zone_transparent ; 
 scalar_t__ local_zone_typetransparent ; 
 scalar_t__ rbtree_search (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int
local_zone_does_not_cover(struct local_zone* z, struct query_info* qinfo,
	int labs)
{
	struct local_data key;
	struct local_data* ld = NULL;
	struct local_rrset* lr = NULL;
	if(z->type == local_zone_always_transparent)
		return 1;
	if(z->type != local_zone_transparent
		&& z->type != local_zone_typetransparent
		&& z->type != local_zone_inform)
		return 0;
	key.node.key = &key;
	key.name = qinfo->qname;
	key.namelen = qinfo->qname_len;
	key.namelabs = labs;
	ld = (struct local_data*)rbtree_search(&z->data, &key.node);
	if(z->type == local_zone_transparent || z->type == local_zone_inform)
		return (ld == NULL);
	if(ld)
		lr = local_data_find_type(ld, qinfo->qtype, 1);
	/* local_zone_typetransparent */
	return (lr == NULL);
}