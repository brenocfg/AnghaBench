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
struct pt_insn_decoder {int /*<<< orphan*/  query; int /*<<< orphan*/  default_image; int /*<<< orphan*/  scache; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_image_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_msec_cache_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_qry_decoder_fini (int /*<<< orphan*/ *) ; 

void pt_insn_decoder_fini(struct pt_insn_decoder *decoder)
{
	if (!decoder)
		return;

	pt_msec_cache_fini(&decoder->scache);
	pt_image_fini(&decoder->default_image);
	pt_qry_decoder_fini(&decoder->query);
}