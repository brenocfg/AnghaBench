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
typedef  size_t uint32_t ;
struct tentry_info {int flags; } ;
struct table_info {int dummy; } ;
struct table_config {int /*<<< orphan*/  count; int /*<<< orphan*/  astate; struct table_algo* ta; } ;
struct table_algo {size_t ta_buf_size; int (* add ) (int /*<<< orphan*/ ,struct table_info*,struct tentry_info*,scalar_t__,size_t*) ;int (* prepare_del ) (struct ip_fw_chain*,struct tentry_info*,scalar_t__) ;int (* del ) (int /*<<< orphan*/ ,struct table_info*,struct tentry_info*,scalar_t__,size_t*) ;} ;
struct ip_fw_chain {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_UH_WLOCK_ASSERT (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int TEI_FLAGS_UPDATED ; 
 int stub1 (int /*<<< orphan*/ ,struct table_info*,struct tentry_info*,scalar_t__,size_t*) ; 
 int stub2 (struct ip_fw_chain*,struct tentry_info*,scalar_t__) ; 
 int stub3 (int /*<<< orphan*/ ,struct table_info*,struct tentry_info*,scalar_t__,size_t*) ; 

__attribute__((used)) static void
rollback_added_entries(struct ip_fw_chain *ch, struct table_config *tc,
    struct table_info *tinfo, struct tentry_info *tei, caddr_t ta_buf_m,
    uint32_t count, uint32_t added)
{
	struct table_algo *ta;
	struct tentry_info *ptei;
	caddr_t v, vv;
	size_t ta_buf_sz;
	int error, i;
	uint32_t num;

	IPFW_UH_WLOCK_ASSERT(ch);

	ta = tc->ta;
	ta_buf_sz = ta->ta_buf_size;
	v = ta_buf_m;
	vv = v + count * ta_buf_sz;
	for (i = 0; i < added; i++, v += ta_buf_sz, vv += ta_buf_sz) {
		ptei = &tei[i];
		if ((ptei->flags & TEI_FLAGS_UPDATED) != 0) {

			/*
			 * We have old value stored by previous
			 * call in @ptei->value. Do add once again
			 * to restore it.
			 */
			error = ta->add(tc->astate, tinfo, ptei, v, &num);
			KASSERT(error == 0, ("rollback UPDATE fail"));
			KASSERT(num == 0, ("rollback UPDATE fail2"));
			continue;
		}

		error = ta->prepare_del(ch, ptei, vv);
		KASSERT(error == 0, ("pre-rollback INSERT failed"));
		error = ta->del(tc->astate, tinfo, ptei, vv, &num);
		KASSERT(error == 0, ("rollback INSERT failed"));
		tc->count -= num;
	}
}