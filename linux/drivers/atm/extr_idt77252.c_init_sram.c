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
typedef  int u32 ;
struct idt77252_dev {int sramsize; int tct_base; int tct_size; int rct_base; int rct_size; int rt_base; int scd_base; int scd_size; int* tst; int tst_size; int abrst_base; int abrst_size; int fifo_base; int fifo_size; int tst_free; int /*<<< orphan*/  name; scalar_t__ tst_index; } ;

/* Variables and functions */
 int** AIR ; 
 int /*<<< orphan*/  IPRINTK (char*,int /*<<< orphan*/ ) ; 
 int** RDF ; 
 int SAR_ABRSTD_SIZE_1K ; 
 int SAR_ABRSTD_SIZE_8K ; 
 int SAR_FBQ0_LOW ; 
 int SAR_FBQ1_LOW ; 
 int SAR_FBQ2_LOW ; 
 int SAR_FBQ3_LOW ; 
 int SAR_FB_SIZE_0 ; 
 int SAR_FB_SIZE_1 ; 
 int SAR_FB_SIZE_2 ; 
 int SAR_FB_SIZE_3 ; 
 scalar_t__ SAR_RCTE_RAWCELLINTEN ; 
 int /*<<< orphan*/  SAR_REG_ABRSTD ; 
 int /*<<< orphan*/  SAR_REG_FBQS0 ; 
 int /*<<< orphan*/  SAR_REG_FBQS1 ; 
 int /*<<< orphan*/  SAR_REG_FBQS2 ; 
 int /*<<< orphan*/  SAR_REG_FBQS3 ; 
 int /*<<< orphan*/  SAR_REG_RTBL ; 
 int /*<<< orphan*/  SAR_REG_RXFD ; 
 int /*<<< orphan*/  SAR_REG_TSTB ; 
 int SAR_RXFD_SIZE_32K ; 
 int SAR_RXFD_SIZE_4K ; 
 int SAR_SRAM_ABRSTD_128_BASE ; 
 int SAR_SRAM_ABRSTD_32_BASE ; 
 int SAR_SRAM_FIFO_128_BASE ; 
 int SAR_SRAM_FIFO_32_BASE ; 
 int SAR_SRAM_RCT_128_BASE ; 
 int SAR_SRAM_RCT_128_TOP ; 
 int SAR_SRAM_RCT_32_BASE ; 
 int SAR_SRAM_RCT_32_TOP ; 
 int SAR_SRAM_RCT_SIZE ; 
 int SAR_SRAM_RT_128_BASE ; 
 int SAR_SRAM_RT_32_BASE ; 
 int SAR_SRAM_SCD_128_BASE ; 
 int SAR_SRAM_SCD_128_TOP ; 
 int SAR_SRAM_SCD_32_BASE ; 
 int SAR_SRAM_SCD_32_TOP ; 
 int SAR_SRAM_SCD_SIZE ; 
 int SAR_SRAM_TCT_128_BASE ; 
 int SAR_SRAM_TCT_128_TOP ; 
 int SAR_SRAM_TCT_32_BASE ; 
 int SAR_SRAM_TCT_32_TOP ; 
 int SAR_SRAM_TCT_SIZE ; 
 int SAR_SRAM_TST1_128_BASE ; 
 int SAR_SRAM_TST1_128_TOP ; 
 int SAR_SRAM_TST1_32_BASE ; 
 int SAR_SRAM_TST1_32_TOP ; 
 int SAR_SRAM_TST2_128_BASE ; 
 int SAR_SRAM_TST2_32_BASE ; 
 int TSTE_OPC_JMP ; 
 int TSTE_OPC_VAR ; 
 int idt77252_sram_write_errors ; 
 int* log_to_rate ; 
 int* rate_to_log ; 
 int /*<<< orphan*/  write_sram (struct idt77252_dev*,int,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_sram(struct idt77252_dev *card)
{
	int i;

	for (i = 0; i < card->sramsize; i += 4)
		write_sram(card, (i >> 2), 0);

	/* set SRAM layout for THIS card */
	if (card->sramsize == (512 * 1024)) {
		card->tct_base = SAR_SRAM_TCT_128_BASE;
		card->tct_size = (SAR_SRAM_TCT_128_TOP - card->tct_base + 1)
		    / SAR_SRAM_TCT_SIZE;
		card->rct_base = SAR_SRAM_RCT_128_BASE;
		card->rct_size = (SAR_SRAM_RCT_128_TOP - card->rct_base + 1)
		    / SAR_SRAM_RCT_SIZE;
		card->rt_base = SAR_SRAM_RT_128_BASE;
		card->scd_base = SAR_SRAM_SCD_128_BASE;
		card->scd_size = (SAR_SRAM_SCD_128_TOP - card->scd_base + 1)
		    / SAR_SRAM_SCD_SIZE;
		card->tst[0] = SAR_SRAM_TST1_128_BASE;
		card->tst[1] = SAR_SRAM_TST2_128_BASE;
		card->tst_size = SAR_SRAM_TST1_128_TOP - card->tst[0] + 1;
		card->abrst_base = SAR_SRAM_ABRSTD_128_BASE;
		card->abrst_size = SAR_ABRSTD_SIZE_8K;
		card->fifo_base = SAR_SRAM_FIFO_128_BASE;
		card->fifo_size = SAR_RXFD_SIZE_32K;
	} else {
		card->tct_base = SAR_SRAM_TCT_32_BASE;
		card->tct_size = (SAR_SRAM_TCT_32_TOP - card->tct_base + 1)
		    / SAR_SRAM_TCT_SIZE;
		card->rct_base = SAR_SRAM_RCT_32_BASE;
		card->rct_size = (SAR_SRAM_RCT_32_TOP - card->rct_base + 1)
		    / SAR_SRAM_RCT_SIZE;
		card->rt_base = SAR_SRAM_RT_32_BASE;
		card->scd_base = SAR_SRAM_SCD_32_BASE;
		card->scd_size = (SAR_SRAM_SCD_32_TOP - card->scd_base + 1)
		    / SAR_SRAM_SCD_SIZE;
		card->tst[0] = SAR_SRAM_TST1_32_BASE;
		card->tst[1] = SAR_SRAM_TST2_32_BASE;
		card->tst_size = (SAR_SRAM_TST1_32_TOP - card->tst[0] + 1);
		card->abrst_base = SAR_SRAM_ABRSTD_32_BASE;
		card->abrst_size = SAR_ABRSTD_SIZE_1K;
		card->fifo_base = SAR_SRAM_FIFO_32_BASE;
		card->fifo_size = SAR_RXFD_SIZE_4K;
	}

	/* Initialize TCT */
	for (i = 0; i < card->tct_size; i++) {
		write_sram(card, i * SAR_SRAM_TCT_SIZE + 0, 0);
		write_sram(card, i * SAR_SRAM_TCT_SIZE + 1, 0);
		write_sram(card, i * SAR_SRAM_TCT_SIZE + 2, 0);
		write_sram(card, i * SAR_SRAM_TCT_SIZE + 3, 0);
		write_sram(card, i * SAR_SRAM_TCT_SIZE + 4, 0);
		write_sram(card, i * SAR_SRAM_TCT_SIZE + 5, 0);
		write_sram(card, i * SAR_SRAM_TCT_SIZE + 6, 0);
		write_sram(card, i * SAR_SRAM_TCT_SIZE + 7, 0);
	}

	/* Initialize RCT */
	for (i = 0; i < card->rct_size; i++) {
		write_sram(card, card->rct_base + i * SAR_SRAM_RCT_SIZE,
				    (u32) SAR_RCTE_RAWCELLINTEN);
		write_sram(card, card->rct_base + i * SAR_SRAM_RCT_SIZE + 1,
				    (u32) 0);
		write_sram(card, card->rct_base + i * SAR_SRAM_RCT_SIZE + 2,
				    (u32) 0);
		write_sram(card, card->rct_base + i * SAR_SRAM_RCT_SIZE + 3,
				    (u32) 0xffffffff);
	}

	writel((SAR_FBQ0_LOW << 28) | (SAR_FB_SIZE_0 / 48), SAR_REG_FBQS0);
	writel((SAR_FBQ1_LOW << 28) | (SAR_FB_SIZE_1 / 48), SAR_REG_FBQS1);
	writel((SAR_FBQ2_LOW << 28) | (SAR_FB_SIZE_2 / 48), SAR_REG_FBQS2);
	writel((SAR_FBQ3_LOW << 28) | (SAR_FB_SIZE_3 / 48), SAR_REG_FBQS3);

	/* Initialize rate table  */
	for (i = 0; i < 256; i++) {
		write_sram(card, card->rt_base + i, log_to_rate[i]);
	}

	for (i = 0; i < 128; i++) {
		unsigned int tmp;

		tmp  = rate_to_log[(i << 2) + 0] << 0;
		tmp |= rate_to_log[(i << 2) + 1] << 8;
		tmp |= rate_to_log[(i << 2) + 2] << 16;
		tmp |= rate_to_log[(i << 2) + 3] << 24;
		write_sram(card, card->rt_base + 256 + i, tmp);
	}

#if 0 /* Fill RDF and AIR tables. */
	for (i = 0; i < 128; i++) {
		unsigned int tmp;

		tmp = RDF[0][(i << 1) + 0] << 16;
		tmp |= RDF[0][(i << 1) + 1] << 0;
		write_sram(card, card->rt_base + 512 + i, tmp);
	}

	for (i = 0; i < 128; i++) {
		unsigned int tmp;

		tmp = AIR[0][(i << 1) + 0] << 16;
		tmp |= AIR[0][(i << 1) + 1] << 0;
		write_sram(card, card->rt_base + 640 + i, tmp);
	}
#endif

	IPRINTK("%s: initialize rate table ...\n", card->name);
	writel(card->rt_base << 2, SAR_REG_RTBL);

	/* Initialize TSTs */
	IPRINTK("%s: initialize TST ...\n", card->name);
	card->tst_free = card->tst_size - 2;	/* last two are jumps */

	for (i = card->tst[0]; i < card->tst[0] + card->tst_size - 2; i++)
		write_sram(card, i, TSTE_OPC_VAR);
	write_sram(card, i++, TSTE_OPC_JMP | (card->tst[0] << 2));
	idt77252_sram_write_errors = 1;
	write_sram(card, i++, TSTE_OPC_JMP | (card->tst[1] << 2));
	idt77252_sram_write_errors = 0;
	for (i = card->tst[1]; i < card->tst[1] + card->tst_size - 2; i++)
		write_sram(card, i, TSTE_OPC_VAR);
	write_sram(card, i++, TSTE_OPC_JMP | (card->tst[1] << 2));
	idt77252_sram_write_errors = 1;
	write_sram(card, i++, TSTE_OPC_JMP | (card->tst[0] << 2));
	idt77252_sram_write_errors = 0;

	card->tst_index = 0;
	writel(card->tst[0] << 2, SAR_REG_TSTB);

	/* Initialize ABRSTD and Receive FIFO */
	IPRINTK("%s: initialize ABRSTD ...\n", card->name);
	writel(card->abrst_size | (card->abrst_base << 2),
	       SAR_REG_ABRSTD);

	IPRINTK("%s: initialize receive fifo ...\n", card->name);
	writel(card->fifo_size | (card->fifo_base << 2),
	       SAR_REG_RXFD);

	IPRINTK("%s: SRAM initialization complete.\n", card->name);
}