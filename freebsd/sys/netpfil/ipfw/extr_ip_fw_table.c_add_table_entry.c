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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ts ;
struct tid_info {int dummy; } ;
struct tentry_info {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  func; } ;
struct tableop_state {scalar_t__ modified; int count; struct tentry_info* tei; struct table_algo* ta; int /*<<< orphan*/  vmask; int /*<<< orphan*/  vshared; struct table_config* tc; TYPE_1__ opstate; struct ip_fw_chain* ch; } ;
struct TYPE_4__ {int /*<<< orphan*/  kidx; int /*<<< orphan*/  refcnt; } ;
struct table_config {int /*<<< orphan*/  count; int /*<<< orphan*/  astate; struct table_algo* ta; TYPE_2__ no; int /*<<< orphan*/  vmask; int /*<<< orphan*/  vshared; } ;
struct table_algo {int (* add ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tentry_info*,char*,int*) ;int /*<<< orphan*/  ta_buf_size; } ;
struct ip_fw_chain {int dummy; } ;
typedef  char* caddr_t ;

/* Variables and functions */
 int IPFW_CTF_ATOMIC ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  KIDX_TO_TI (struct ip_fw_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_ADD ; 
 int TA_BUF_SZ ; 
 int /*<<< orphan*/  add_toperation_state (struct ip_fw_chain*,struct tableop_state*) ; 
 int check_table_limit (struct table_config*,struct tentry_info*) ; 
 int check_table_space (struct ip_fw_chain*,struct tableop_state*,struct table_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  del_toperation_state (struct ip_fw_chain*,struct tableop_state*) ; 
 int find_ref_table (struct ip_fw_chain*,struct tid_info*,struct tentry_info*,int,int /*<<< orphan*/ ,struct table_config**) ; 
 int /*<<< orphan*/  flush_batch_buffer (struct ip_fw_chain*,struct table_algo*,struct tentry_info*,int,int,char*,char*) ; 
 int /*<<< orphan*/  ipfw_garbage_table_values (struct ip_fw_chain*,struct table_config*,struct tentry_info*,int,int) ; 
 int ipfw_link_table_values (struct ip_fw_chain*,struct tableop_state*) ; 
 int /*<<< orphan*/  memset (struct tableop_state*,int /*<<< orphan*/ ,int) ; 
 int prepare_batch_buffer (struct ip_fw_chain*,struct table_algo*,struct tentry_info*,int,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  rollback_add_entry ; 
 int /*<<< orphan*/  rollback_added_entries (struct ip_fw_chain*,struct table_config*,int /*<<< orphan*/ ,struct tentry_info*,char*,int,int) ; 
 int /*<<< orphan*/  store_tei_result (struct tentry_info*,int /*<<< orphan*/ ,int,int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tentry_info*,char*,int*) ; 

int
add_table_entry(struct ip_fw_chain *ch, struct tid_info *ti,
    struct tentry_info *tei, uint8_t flags, uint32_t count)
{
	struct table_config *tc;
	struct table_algo *ta;
	uint16_t kidx;
	int error, first_error, i, rollback;
	uint32_t num, numadd;
	struct tentry_info *ptei;
	struct tableop_state ts;
	char ta_buf[TA_BUF_SZ];
	caddr_t ta_buf_m, v;

	memset(&ts, 0, sizeof(ts));
	ta = NULL;
	IPFW_UH_WLOCK(ch);

	/*
	 * Find and reference existing table.
	 */
restart:
	if (ts.modified != 0) {
		IPFW_UH_WUNLOCK(ch);
		flush_batch_buffer(ch, ta, tei, count, rollback,
		    ta_buf_m, ta_buf);
		memset(&ts, 0, sizeof(ts));
		ta = NULL;
		IPFW_UH_WLOCK(ch);
	}

	error = find_ref_table(ch, ti, tei, count, OP_ADD, &tc);
	if (error != 0) {
		IPFW_UH_WUNLOCK(ch);
		return (error);
	}
	ta = tc->ta;

	/* Fill in tablestate */
	ts.ch = ch;
	ts.opstate.func = rollback_add_entry;
	ts.tc = tc;
	ts.vshared = tc->vshared;
	ts.vmask = tc->vmask;
	ts.ta = ta;
	ts.tei = tei;
	ts.count = count;
	rollback = 0;
	add_toperation_state(ch, &ts);
	IPFW_UH_WUNLOCK(ch);

	/* Allocate memory and prepare record(s) */
	/* Pass stack buffer by default */
	ta_buf_m = ta_buf;
	error = prepare_batch_buffer(ch, ta, tei, count, OP_ADD, &ta_buf_m);

	IPFW_UH_WLOCK(ch);
	del_toperation_state(ch, &ts);
	/* Drop reference we've used in first search */
	tc->no.refcnt--;

	/* Check prepare_batch_buffer() error */
	if (error != 0)
		goto cleanup;

	/*
	 * Check if table swap has happened.
	 * (so table algo might be changed).
	 * Restart operation to achieve consistent behavior.
	 */
	if (ts.modified != 0)
		goto restart;

	/*
	 * Link all values values to shared/per-table value array.
	 *
	 * May release/reacquire UH_WLOCK.
	 */
	error = ipfw_link_table_values(ch, &ts);
	if (error != 0)
		goto cleanup;
	if (ts.modified != 0)
		goto restart;

	/*
	 * Ensure we are able to add all entries without additional
	 * memory allocations. May release/reacquire UH_WLOCK.
	 */
	kidx = tc->no.kidx;
	error = check_table_space(ch, &ts, tc, KIDX_TO_TI(ch, kidx), count);
	if (error != 0)
		goto cleanup;
	if (ts.modified != 0)
		goto restart;

	/* We've got valid table in @tc. Let's try to add data */
	kidx = tc->no.kidx;
	ta = tc->ta;
	numadd = 0;
	first_error = 0;

	IPFW_WLOCK(ch);

	v = ta_buf_m;
	for (i = 0; i < count; i++, v += ta->ta_buf_size) {
		ptei = &tei[i];
		num = 0;
		/* check limit before adding */
		if ((error = check_table_limit(tc, ptei)) == 0) {
			error = ta->add(tc->astate, KIDX_TO_TI(ch, kidx),
			    ptei, v, &num);
			/* Set status flag to inform userland */
			store_tei_result(ptei, OP_ADD, error, num);
		}
		if (error == 0) {
			/* Update number of records to ease limit checking */
			tc->count += num;
			numadd += num;
			continue;
		}

		if (first_error == 0)
			first_error = error;

		/*
		 * Some error have happened. Check our atomicity
		 * settings: continue if atomicity is not required,
		 * rollback changes otherwise.
		 */
		if ((flags & IPFW_CTF_ATOMIC) == 0)
			continue;

		rollback_added_entries(ch, tc, KIDX_TO_TI(ch, kidx),
		    tei, ta_buf_m, count, i);

		rollback = 1;
		break;
	}

	IPFW_WUNLOCK(ch);

	ipfw_garbage_table_values(ch, tc, tei, count, rollback);

	/* Permit post-add algorithm grow/rehash. */
	if (numadd != 0)
		check_table_space(ch, NULL, tc, KIDX_TO_TI(ch, kidx), 0);

	/* Return first error to user, if any */
	error = first_error;

cleanup:
	IPFW_UH_WUNLOCK(ch);

	flush_batch_buffer(ch, ta, tei, count, rollback, ta_buf_m, ta_buf);
	
	return (error);
}