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
typedef  scalar_t__ u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;

/* Variables and functions */
 int DBG_STATUS_DUMP_BUF_TOO_SMALL ; 
 int DBG_STATUS_OK ; 
 int ecore_dbg_grc_get_dump_buf_size (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__*) ; 
 int /*<<< orphan*/  ecore_dbg_grc_set_params_default (struct ecore_hwfn*) ; 
 int ecore_grc_dump (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  ecore_static_asserts () ; 

enum dbg_status ecore_dbg_grc_dump(struct ecore_hwfn *p_hwfn,
								   struct ecore_ptt *p_ptt,
								   u32 *dump_buf,
								   u32 buf_size_in_dwords,
								   u32 *num_dumped_dwords)
{
	u32 needed_buf_size_in_dwords;
	enum dbg_status status;

	*num_dumped_dwords = 0;

	status = ecore_dbg_grc_get_dump_buf_size(p_hwfn, p_ptt, &needed_buf_size_in_dwords);
	if (status != DBG_STATUS_OK)
		return status;

	if (buf_size_in_dwords < needed_buf_size_in_dwords)
		return DBG_STATUS_DUMP_BUF_TOO_SMALL;

	/* Doesn't do anything, needed for compile time asserts */
	ecore_static_asserts();

	/* GRC Dump */
	status = ecore_grc_dump(p_hwfn, p_ptt, dump_buf, true, num_dumped_dwords);

	/* Reveret GRC params to their default */
	ecore_dbg_grc_set_params_default(p_hwfn);

	return status;
}