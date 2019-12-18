#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct respip_client_info {int dummy; } ;
struct query_info {int dummy; } ;
struct TYPE_3__ {int is_priming; int is_valrec; struct respip_client_info* client_info; int /*<<< orphan*/  query_flags; struct query_info qinfo; } ;
struct TYPE_4__ {struct mesh_state* key; } ;
struct mesh_state {TYPE_1__ s; int /*<<< orphan*/ * unique; TYPE_2__ node; } ;
struct mesh_area {int /*<<< orphan*/  all; } ;

/* Variables and functions */
 scalar_t__ rbtree_search (int /*<<< orphan*/ *,struct mesh_state*) ; 

struct mesh_state* mesh_area_find(struct mesh_area* mesh,
	struct respip_client_info* cinfo, struct query_info* qinfo,
	uint16_t qflags, int prime, int valrec)
{
	struct mesh_state key;
	struct mesh_state* result;

	key.node.key = &key;
	key.s.is_priming = prime;
	key.s.is_valrec = valrec;
	key.s.qinfo = *qinfo;
	key.s.query_flags = qflags;
	/* We are searching for a similar mesh state when we DO want to
	 * aggregate the state. Thus unique is set to NULL. (default when we
	 * desire aggregation).*/
	key.unique = NULL;
	key.s.client_info = cinfo;
	
	result = (struct mesh_state*)rbtree_search(&mesh->all, &key);
	return result;
}