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
struct TYPE_2__ {int query_flags; int /*<<< orphan*/  client_info; int /*<<< orphan*/  qinfo; scalar_t__ is_valrec; scalar_t__ is_priming; } ;
struct mesh_state {scalar_t__ unique; TYPE_1__ s; } ;

/* Variables and functions */
 int BIT_CD ; 
 int BIT_RD ; 
 int client_info_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int query_info_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
mesh_state_compare(const void* ap, const void* bp)
{
	struct mesh_state* a = (struct mesh_state*)ap;
	struct mesh_state* b = (struct mesh_state*)bp;
	int cmp;

	if(a->unique < b->unique)
		return -1;
	if(a->unique > b->unique)
		return 1;

	if(a->s.is_priming && !b->s.is_priming)
		return -1;
	if(!a->s.is_priming && b->s.is_priming)
		return 1;

	if(a->s.is_valrec && !b->s.is_valrec)
		return -1;
	if(!a->s.is_valrec && b->s.is_valrec)
		return 1;

	if((a->s.query_flags&BIT_RD) && !(b->s.query_flags&BIT_RD))
		return -1;
	if(!(a->s.query_flags&BIT_RD) && (b->s.query_flags&BIT_RD))
		return 1;

	if((a->s.query_flags&BIT_CD) && !(b->s.query_flags&BIT_CD))
		return -1;
	if(!(a->s.query_flags&BIT_CD) && (b->s.query_flags&BIT_CD))
		return 1;

	cmp = query_info_compare(&a->s.qinfo, &b->s.qinfo);
	if(cmp != 0)
		return cmp;
	return client_info_compare(a->s.client_info, b->s.client_info);
}