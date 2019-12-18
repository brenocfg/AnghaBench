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
typedef  int uint32_t ;
struct tentry_info {scalar_t__ subtype; int /*<<< orphan*/  value; } ;
struct table_info {struct radix_node_head* xstate; struct radix_node_head* state; } ;
struct ta_buf_radix {struct radix_node* ent_ptr; int /*<<< orphan*/  mask_ptr; int /*<<< orphan*/  addr_ptr; } ;
struct radix_node_head {int /*<<< orphan*/  rh; struct radix_node* (* rnh_deladdr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct radix_node {int dummy; } ;
struct radix_cfg {int /*<<< orphan*/  count6; int /*<<< orphan*/  count4; } ;
struct radix_addr_xentry {int /*<<< orphan*/  value; } ;
struct radix_addr_entry {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int ENOENT ; 
 struct radix_node* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ta_del_radix(void *ta_state, struct table_info *ti, struct tentry_info *tei,
    void *ta_buf, uint32_t *pnum)
{
	struct radix_cfg *cfg;
	struct radix_node_head *rnh;
	struct radix_node *rn;
	struct ta_buf_radix *tb;

	cfg = (struct radix_cfg *)ta_state;
	tb = (struct ta_buf_radix *)ta_buf;

	if (tei->subtype == AF_INET)
		rnh = ti->state;
	else
		rnh = ti->xstate;

	rn = rnh->rnh_deladdr(tb->addr_ptr, tb->mask_ptr, &rnh->rh);

	if (rn == NULL)
		return (ENOENT);

	/* Save entry value to @tei */
	if (tei->subtype == AF_INET)
		tei->value = ((struct radix_addr_entry *)rn)->value;
	else
		tei->value = ((struct radix_addr_xentry *)rn)->value;

	tb->ent_ptr = rn;
	
	if (tei->subtype == AF_INET)
		cfg->count4--;
	else
		cfg->count6--;
	*pnum = 1;

	return (0);
}