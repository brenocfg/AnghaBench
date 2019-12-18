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
struct pt_query_decoder {int /*<<< orphan*/  tnt; } ;

/* Variables and functions */
 int pt_qry_cache_tnt (struct pt_query_decoder*) ; 
 int pt_qry_status_flags (struct pt_query_decoder*) ; 
 scalar_t__ pt_tnt_cache_is_empty (int /*<<< orphan*/ *) ; 
 int pt_tnt_cache_query (int /*<<< orphan*/ *) ; 
 int pte_invalid ; 

int pt_qry_cond_branch(struct pt_query_decoder *decoder, int *taken)
{
	int errcode, query;

	if (!decoder || !taken)
		return -pte_invalid;

	/* We cache the latest tnt packet in the decoder. Let's re-fill the
	 * cache in case it is empty.
	 */
	if (pt_tnt_cache_is_empty(&decoder->tnt)) {
		errcode = pt_qry_cache_tnt(decoder);
		if (errcode < 0)
			return errcode;
	}

	query = pt_tnt_cache_query(&decoder->tnt);
	if (query < 0)
		return query;

	*taken = query;

	return pt_qry_status_flags(decoder);
}