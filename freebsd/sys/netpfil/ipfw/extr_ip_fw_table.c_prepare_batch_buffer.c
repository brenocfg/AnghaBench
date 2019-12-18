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
struct tentry_info {int dummy; } ;
struct table_algo {size_t ta_buf_size; int (* prepare_add ) (struct ip_fw_chain*,struct tentry_info*,size_t) ;int (* prepare_del ) (struct ip_fw_chain*,struct tentry_info*,size_t) ;} ;
struct ip_fw_chain {int dummy; } ;
typedef  size_t caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int OP_ADD ; 
 int /*<<< orphan*/  TA_BUF_SZ ; 
 size_t malloc (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct ip_fw_chain*,struct tentry_info*,size_t) ; 
 int stub2 (struct ip_fw_chain*,struct tentry_info*,size_t) ; 

__attribute__((used)) static int
prepare_batch_buffer(struct ip_fw_chain *ch, struct table_algo *ta,
    struct tentry_info *tei, uint32_t count, int op, caddr_t *ta_buf)
{
	caddr_t ta_buf_m, v;
	size_t ta_buf_sz, sz;
	struct tentry_info *ptei;
	int error, i;

	error = 0;
	ta_buf_sz = ta->ta_buf_size;
	if (count == 1) {
		/* Single add/delete, use on-stack buffer */
		memset(*ta_buf, 0, TA_BUF_SZ);
		ta_buf_m = *ta_buf;
	} else {

		/*
		 * Multiple adds/deletes, allocate larger buffer
		 *
		 * Note we need 2xcount buffer for add case:
		 * we have hold both ADD state
		 * and DELETE state (this may be needed
		 * if we need to rollback all changes)
		 */
		sz = count * ta_buf_sz;
		ta_buf_m = malloc((op == OP_ADD) ? sz * 2 : sz, M_TEMP,
		    M_WAITOK | M_ZERO);
	}

	v = ta_buf_m;
	for (i = 0; i < count; i++, v += ta_buf_sz) {
		ptei = &tei[i];
		error = (op == OP_ADD) ?
		    ta->prepare_add(ch, ptei, v) : ta->prepare_del(ch, ptei, v);

		/*
		 * Some syntax error (incorrect mask, or address, or
		 * anything). Return error regardless of atomicity
		 * settings.
		 */
		if (error != 0)
			break;
	}

	*ta_buf = ta_buf_m;
	return (error);
}