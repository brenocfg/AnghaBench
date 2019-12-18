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
struct respip_client_info {scalar_t__ taglen; scalar_t__ tag_actions_size; scalar_t__ tag_datas; scalar_t__ view; scalar_t__ respip_set; int /*<<< orphan*/  tag_actions; int /*<<< orphan*/  taglist; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
client_info_compare(const struct respip_client_info* ci_a,
	const struct respip_client_info* ci_b)
{
	int cmp;

	if(!ci_a && !ci_b)
		return 0;
	if(ci_a && !ci_b)
		return -1;
	if(!ci_a && ci_b)
		return 1;
	if(ci_a->taglen != ci_b->taglen)
		return (ci_a->taglen < ci_b->taglen) ? -1 : 1;
	cmp = memcmp(ci_a->taglist, ci_b->taglist, ci_a->taglen);
	if(cmp != 0)
		return cmp;
	if(ci_a->tag_actions_size != ci_b->tag_actions_size)
		return (ci_a->tag_actions_size < ci_b->tag_actions_size) ?
			-1 : 1;
	cmp = memcmp(ci_a->tag_actions, ci_b->tag_actions,
		ci_a->tag_actions_size);
	if(cmp != 0)
		return cmp;
	if(ci_a->tag_datas != ci_b->tag_datas)
		return ci_a->tag_datas < ci_b->tag_datas ? -1 : 1;
	if(ci_a->view != ci_b->view)
		return ci_a->view < ci_b->view ? -1 : 1;
	/* For the unbound daemon these should be non-NULL and identical,
	 * but we check that just in case. */
	if(ci_a->respip_set != ci_b->respip_set)
		return ci_a->respip_set < ci_b->respip_set ? -1 : 1;
	return 0;
}