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
struct tentry_info {scalar_t__ subtype; int value; int flags; } ;
struct table_info {struct radix_node_head* xstate; struct radix_node_head* state; } ;
struct ta_buf_radix {int /*<<< orphan*/ * ent_ptr; int /*<<< orphan*/  mask_ptr; int /*<<< orphan*/  addr_ptr; } ;
struct radix_node_head {int /*<<< orphan*/  rh; struct radix_node* (* rnh_addaddr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;struct radix_node* (* rnh_lookup ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct radix_node {int dummy; } ;
struct radix_cfg {int /*<<< orphan*/  count6; int /*<<< orphan*/  count4; } ;
struct radix_addr_xentry {int value; } ;
struct radix_addr_entry {int value; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EEXIST ; 
 int EFBIG ; 
 int EINVAL ; 
 int TEI_FLAGS_DONTADD ; 
 int TEI_FLAGS_UPDATE ; 
 int TEI_FLAGS_UPDATED ; 
 struct radix_node* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct radix_node* stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ta_add_radix(void *ta_state, struct table_info *ti, struct tentry_info *tei,
    void *ta_buf, uint32_t *pnum)
{
	struct radix_cfg *cfg;
	struct radix_node_head *rnh;
	struct radix_node *rn;
	struct ta_buf_radix *tb;
	uint32_t *old_value, value;

	cfg = (struct radix_cfg *)ta_state;
	tb = (struct ta_buf_radix *)ta_buf;

	/* Save current entry value from @tei */
	if (tei->subtype == AF_INET) {
		rnh = ti->state;
		((struct radix_addr_entry *)tb->ent_ptr)->value = tei->value;
	} else {
		rnh = ti->xstate;
		((struct radix_addr_xentry *)tb->ent_ptr)->value = tei->value;
	}

	/* Search for an entry first */
	rn = rnh->rnh_lookup(tb->addr_ptr, tb->mask_ptr, &rnh->rh);
	if (rn != NULL) {
		if ((tei->flags & TEI_FLAGS_UPDATE) == 0)
			return (EEXIST);
		/* Record already exists. Update value if we're asked to */
		if (tei->subtype == AF_INET)
			old_value = &((struct radix_addr_entry *)rn)->value;
		else
			old_value = &((struct radix_addr_xentry *)rn)->value;

		value = *old_value;
		*old_value = tei->value;
		tei->value = value;

		/* Indicate that update has happened instead of addition */
		tei->flags |= TEI_FLAGS_UPDATED;
		*pnum = 0;

		return (0);
	}

	if ((tei->flags & TEI_FLAGS_DONTADD) != 0)
		return (EFBIG);

	rn = rnh->rnh_addaddr(tb->addr_ptr, tb->mask_ptr, &rnh->rh,tb->ent_ptr);
	if (rn == NULL) {
		/* Unknown error */
		return (EINVAL);
	}
	
	if (tei->subtype == AF_INET)
		cfg->count4++;
	else
		cfg->count6++;
	tb->ent_ptr = NULL;
	*pnum = 1;

	return (0);
}