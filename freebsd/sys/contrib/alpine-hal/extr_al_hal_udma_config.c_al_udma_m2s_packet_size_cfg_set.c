#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct al_udma_m2s_pkt_len_conf {scalar_t__ encode_64k_as_zero; scalar_t__ max_pkt_size; } ;
struct al_udma {scalar_t__ type; TYPE_3__* udma_regs; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  cfg_len; } ;
struct TYPE_5__ {TYPE_1__ m2s; } ;
struct TYPE_6__ {TYPE_2__ m2s; } ;

/* Variables and functions */
 scalar_t__ AL_TRUE ; 
 int EINVAL ; 
 scalar_t__ UDMA_M2S_CFG_LEN_ENCODE_64K ; 
 scalar_t__ UDMA_M2S_CFG_LEN_MAX_PKT_SIZE_MASK ; 
 scalar_t__ UDMA_TX ; 
 int /*<<< orphan*/  al_assert (int) ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,scalar_t__) ; 

int al_udma_m2s_packet_size_cfg_set(struct al_udma *udma,
				struct al_udma_m2s_pkt_len_conf *conf)
{
	uint32_t reg = al_reg_read32(&udma->udma_regs->m2s.m2s.cfg_len);
	uint32_t max_supported_size = UDMA_M2S_CFG_LEN_MAX_PKT_SIZE_MASK;

	al_assert(udma->type == UDMA_TX);

	if (conf->encode_64k_as_zero == AL_TRUE)
		max_supported_size += 1;	/* 64K */

	if (conf->max_pkt_size > max_supported_size) {
		al_err("udma [%s]: requested max_pkt_size (0x%x) exceeds the"
			"supported limit (0x%x)\n", udma->name,
			 conf->max_pkt_size, max_supported_size);
		return -EINVAL;
	}

	reg &= ~UDMA_M2S_CFG_LEN_ENCODE_64K;
	if (conf->encode_64k_as_zero == AL_TRUE)
		reg |= UDMA_M2S_CFG_LEN_ENCODE_64K;
	else
		reg &= ~UDMA_M2S_CFG_LEN_ENCODE_64K;

	reg &= ~UDMA_M2S_CFG_LEN_MAX_PKT_SIZE_MASK;
	reg |= conf->max_pkt_size;

	al_reg_write32(&udma->udma_regs->m2s.m2s.cfg_len, reg);
	return 0;
}