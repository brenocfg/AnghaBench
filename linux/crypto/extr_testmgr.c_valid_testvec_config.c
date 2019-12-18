#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct testvec_config {scalar_t__ iv_offset; scalar_t__ finalization_type; int req_flags; scalar_t__ nosimd; scalar_t__ iv_offset_relative_to_alignmask; TYPE_1__* dst_divs; TYPE_1__* src_divs; int /*<<< orphan*/ * name; } ;
struct TYPE_4__ {scalar_t__ proportion_of_total; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__*) ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 scalar_t__ FINALIZATION_TYPE_DIGEST ; 
 scalar_t__ MAX_ALGAPI_ALIGNMASK ; 
 int SGDIVS_HAVE_FLUSHES ; 
 int SGDIVS_HAVE_NOSIMD ; 
 scalar_t__ memchr_inv (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  valid_sg_divisions (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool valid_testvec_config(const struct testvec_config *cfg)
{
	int flags = 0;

	if (cfg->name == NULL)
		return false;

	if (!valid_sg_divisions(cfg->src_divs, ARRAY_SIZE(cfg->src_divs),
				&flags))
		return false;

	if (cfg->dst_divs[0].proportion_of_total) {
		if (!valid_sg_divisions(cfg->dst_divs,
					ARRAY_SIZE(cfg->dst_divs), &flags))
			return false;
	} else {
		if (memchr_inv(cfg->dst_divs, 0, sizeof(cfg->dst_divs)))
			return false;
		/* defaults to dst_divs=src_divs */
	}

	if (cfg->iv_offset +
	    (cfg->iv_offset_relative_to_alignmask ? MAX_ALGAPI_ALIGNMASK : 0) >
	    MAX_ALGAPI_ALIGNMASK + 1)
		return false;

	if ((flags & (SGDIVS_HAVE_FLUSHES | SGDIVS_HAVE_NOSIMD)) &&
	    cfg->finalization_type == FINALIZATION_TYPE_DIGEST)
		return false;

	if ((cfg->nosimd || (flags & SGDIVS_HAVE_NOSIMD)) &&
	    (cfg->req_flags & CRYPTO_TFM_REQ_MAY_SLEEP))
		return false;

	return true;
}