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
struct pt_insn_decoder {int /*<<< orphan*/  query; } ;
struct pt_config {int dummy; } ;

/* Variables and functions */
 struct pt_config const* pt_qry_get_config (int /*<<< orphan*/ *) ; 

const struct pt_config *
pt_insn_get_config(const struct pt_insn_decoder *decoder)
{
	if (!decoder)
		return NULL;

	return pt_qry_get_config(&decoder->query);
}