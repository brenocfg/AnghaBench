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
struct pt_insn_decoder {int /*<<< orphan*/  scache; int /*<<< orphan*/  default_image; int /*<<< orphan*/ * image; int /*<<< orphan*/  query; int /*<<< orphan*/  flags; } ;
struct pt_config {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int pt_config_from_user (struct pt_config*,struct pt_config const*) ; 
 int /*<<< orphan*/  pt_image_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pt_insn_init_qry_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_insn_reset (struct pt_insn_decoder*) ; 
 int pt_msec_cache_init (int /*<<< orphan*/ *) ; 
 int pt_qry_decoder_init (int /*<<< orphan*/ *,struct pt_config*) ; 
 int pte_internal ; 

int pt_insn_decoder_init(struct pt_insn_decoder *decoder,
			 const struct pt_config *uconfig)
{
	struct pt_config config;
	int errcode;

	if (!decoder)
		return -pte_internal;

	errcode = pt_config_from_user(&config, uconfig);
	if (errcode < 0)
		return errcode;

	/* The user supplied decoder flags. */
	decoder->flags = config.flags;

	/* Set the flags we need for the query decoder we use. */
	errcode = pt_insn_init_qry_flags(&config.flags, &decoder->flags);
	if (errcode < 0)
		return errcode;

	errcode = pt_qry_decoder_init(&decoder->query, &config);
	if (errcode < 0)
		return errcode;

	pt_image_init(&decoder->default_image, NULL);
	decoder->image = &decoder->default_image;

	errcode = pt_msec_cache_init(&decoder->scache);
	if (errcode < 0)
		return errcode;

	pt_insn_reset(decoder);

	return 0;
}