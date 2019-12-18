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
typedef  char u8 ;
typedef  int u16 ;
struct i40e_hw {int debug_mask; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr_low; int /*<<< orphan*/  addr_high; } ;
struct TYPE_4__ {int /*<<< orphan*/  param1; int /*<<< orphan*/  param0; } ;
struct TYPE_6__ {TYPE_2__ external; TYPE_1__ internal; } ;
struct i40e_aq_desc {scalar_t__ datalen; scalar_t__ opcode; scalar_t__ flags; scalar_t__ retval; TYPE_3__ params; int /*<<< orphan*/  cookie_low; int /*<<< orphan*/  cookie_high; } ;
typedef  enum i40e_debug_mask { ____Placeholder_i40e_debug_mask } i40e_debug_mask ;
typedef  int /*<<< orphan*/  d_buf ;

/* Variables and functions */
 int LE16_TO_CPU (scalar_t__) ; 
 int /*<<< orphan*/  LE32_TO_CPU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_debug (struct i40e_hw*,int,char*,...) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

void i40e_debug_aq(struct i40e_hw *hw, enum i40e_debug_mask mask, void *desc,
		   void *buffer, u16 buf_len)
{
	struct i40e_aq_desc *aq_desc = (struct i40e_aq_desc *)desc;
	u8 *buf = (u8 *)buffer;
	u16 len;
	u16 i = 0;

	if ((!(mask & hw->debug_mask)) || (desc == NULL))
		return;

	len = LE16_TO_CPU(aq_desc->datalen);

	i40e_debug(hw, mask,
		   "AQ CMD: opcode 0x%04X, flags 0x%04X, datalen 0x%04X, retval 0x%04X\n",
		   LE16_TO_CPU(aq_desc->opcode),
		   LE16_TO_CPU(aq_desc->flags),
		   LE16_TO_CPU(aq_desc->datalen),
		   LE16_TO_CPU(aq_desc->retval));
	i40e_debug(hw, mask, "\tcookie (h,l) 0x%08X 0x%08X\n",
		   LE32_TO_CPU(aq_desc->cookie_high),
		   LE32_TO_CPU(aq_desc->cookie_low));
	i40e_debug(hw, mask, "\tparam (0,1)  0x%08X 0x%08X\n",
		   LE32_TO_CPU(aq_desc->params.internal.param0),
		   LE32_TO_CPU(aq_desc->params.internal.param1));
	i40e_debug(hw, mask, "\taddr (h,l)   0x%08X 0x%08X\n",
		   LE32_TO_CPU(aq_desc->params.external.addr_high),
		   LE32_TO_CPU(aq_desc->params.external.addr_low));

	if ((buffer != NULL) && (aq_desc->datalen != 0)) {
		i40e_debug(hw, mask, "AQ CMD Buffer:\n");
		if (buf_len < len)
			len = buf_len;
		/* write the full 16-byte chunks */
		for (i = 0; i < (len - 16); i += 16)
			i40e_debug(hw, mask,
				   "\t0x%04X  %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n",
				   i, buf[i], buf[i+1], buf[i+2], buf[i+3],
				   buf[i+4], buf[i+5], buf[i+6], buf[i+7],
				   buf[i+8], buf[i+9], buf[i+10], buf[i+11],
				   buf[i+12], buf[i+13], buf[i+14], buf[i+15]);
		/* the most we could have left is 16 bytes, pad with zeros */
		if (i < len) {
			char d_buf[16];
			int j, i_sav;

			i_sav = i;
			memset(d_buf, 0, sizeof(d_buf));
			for (j = 0; i < len; j++, i++)
				d_buf[j] = buf[i];
			i40e_debug(hw, mask,
				   "\t0x%04X  %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n",
				   i_sav, d_buf[0], d_buf[1], d_buf[2], d_buf[3],
				   d_buf[4], d_buf[5], d_buf[6], d_buf[7],
				   d_buf[8], d_buf[9], d_buf[10], d_buf[11],
				   d_buf[12], d_buf[13], d_buf[14], d_buf[15]);
		}
	}
}