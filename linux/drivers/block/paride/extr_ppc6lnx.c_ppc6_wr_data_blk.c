#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {int mode; int /*<<< orphan*/  lpt_addr; int /*<<< orphan*/  cur_ctrl; } ;
typedef  TYPE_1__ Interface ;

/* Variables and functions */
 int CMD_PREFIX_RESET ; 
 int CMD_PREFIX_SET ; 
#define  PPCMODE_BI_FW 134 
#define  PPCMODE_BI_SW 133 
#define  PPCMODE_EPP_BYTE 132 
#define  PPCMODE_EPP_DWORD 131 
#define  PPCMODE_EPP_WORD 130 
#define  PPCMODE_UNI_FW 129 
#define  PPCMODE_UNI_SW 128 
 int PREFIX_FASTWR ; 
 int /*<<< orphan*/  data_stb ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_stb ; 
 int /*<<< orphan*/  ppc6_send_cmd (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ppc6_wait_for_fifo (TYPE_1__*) ; 

__attribute__((used)) static void ppc6_wr_data_blk(Interface *ppc, u8 *data, long count)
{
	switch(ppc->mode)
	{
		case PPCMODE_UNI_SW :
		case PPCMODE_BI_SW :
		{
			while(count--)
			{
				outb(*data++, ppc->lpt_addr);

				ppc->cur_ctrl ^= data_stb;

				outb(ppc->cur_ctrl, ppc->lpt_addr + 2);
			}

			break;
		}

		case PPCMODE_UNI_FW :
		case PPCMODE_BI_FW :
		{
			u8 this, last;

			ppc6_send_cmd(ppc,(CMD_PREFIX_SET | PREFIX_FASTWR));

			ppc->cur_ctrl |= port_stb;

			outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

			last = *data;

			outb(last, ppc->lpt_addr);

			while(count)
			{
				this = *data++;
				count--;

				if (this == last)
				{
					ppc->cur_ctrl ^= data_stb;

					outb(ppc->cur_ctrl, ppc->lpt_addr + 2);
				}
				else
				{
					outb(this, ppc->lpt_addr);

					last = this;
				}
			}

			ppc->cur_ctrl &= ~port_stb;

			outb(ppc->cur_ctrl, ppc->lpt_addr + 2);

			ppc6_send_cmd(ppc,(CMD_PREFIX_RESET | PREFIX_FASTWR));

			break;
		}

		case PPCMODE_EPP_BYTE :
		{
			while(count)
			{
				outb(*data++,ppc->lpt_addr + 4);
				count--;
			}

			ppc6_wait_for_fifo(ppc);

			break;
		}

		case PPCMODE_EPP_WORD :
		{
			while(count > 1)
			{
				outw(*((u16 *)data),ppc->lpt_addr + 4);
				data  += 2;
				count -= 2;
			}

			while(count)
			{
				outb(*data++,ppc->lpt_addr + 4);
				count--;
			}

			ppc6_wait_for_fifo(ppc);

			break;
		}

		case PPCMODE_EPP_DWORD :
		{
			while(count > 3)
			{
				outl(*((u32 *)data),ppc->lpt_addr + 4);
				data  += 4;
				count -= 4;
			}

			while(count)
			{
				outb(*data++,ppc->lpt_addr + 4);
				count--;
			}

			ppc6_wait_for_fifo(ppc);

			break;
		}
	}
}