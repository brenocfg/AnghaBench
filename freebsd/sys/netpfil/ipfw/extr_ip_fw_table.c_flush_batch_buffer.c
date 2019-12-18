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
struct tentry_info {int /*<<< orphan*/ * ptv; } ;
struct table_algo {size_t ta_buf_size; int /*<<< orphan*/  (* flush_entry ) (struct ip_fw_chain*,struct tentry_info*,int /*<<< orphan*/ *) ;} ;
struct ip_fw_chain {int dummy; } ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_IPFW ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ip_fw_chain*,struct tentry_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct ip_fw_chain*,struct tentry_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
flush_batch_buffer(struct ip_fw_chain *ch, struct table_algo *ta,
    struct tentry_info *tei, uint32_t count, int rollback,
    caddr_t ta_buf_m, caddr_t ta_buf)
{
	caddr_t v;
	struct tentry_info *ptei;
	size_t ta_buf_sz;
	int i;

	ta_buf_sz = ta->ta_buf_size;

	/* Run cleaning callback anyway */
	v = ta_buf_m;
	for (i = 0; i < count; i++, v += ta_buf_sz) {
		ptei = &tei[i];
		ta->flush_entry(ch, ptei, v);
		if (ptei->ptv != NULL) {
			free(ptei->ptv, M_IPFW);
			ptei->ptv = NULL;
		}
	}

	/* Clean up "deleted" state in case of rollback */
	if (rollback != 0) {
		v = ta_buf_m + count * ta_buf_sz;
		for (i = 0; i < count; i++, v += ta_buf_sz)
			ta->flush_entry(ch, &tei[i], v);
	}

	if (ta_buf_m != ta_buf)
		free(ta_buf_m, M_TEMP);
}