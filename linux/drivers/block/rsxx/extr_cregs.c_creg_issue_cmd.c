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
struct rsxx_cardinfo {scalar_t__ regmap; int /*<<< orphan*/  eeh_state; } ;
struct creg_cmd {scalar_t__ addr; scalar_t__ cnt8; scalar_t__ op; int /*<<< orphan*/  stream; scalar_t__ buf; } ;

/* Variables and functions */
 scalar_t__ CREG_ADD ; 
 scalar_t__ CREG_CMD ; 
 scalar_t__ CREG_CNT ; 
 scalar_t__ CREG_OP_WRITE ; 
 int copy_to_creg_data (struct rsxx_cardinfo*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void creg_issue_cmd(struct rsxx_cardinfo *card, struct creg_cmd *cmd)
{
	int st;

	if (unlikely(card->eeh_state))
		return;

	iowrite32(cmd->addr, card->regmap + CREG_ADD);
	iowrite32(cmd->cnt8, card->regmap + CREG_CNT);

	if (cmd->op == CREG_OP_WRITE) {
		if (cmd->buf) {
			st = copy_to_creg_data(card, cmd->cnt8,
					       cmd->buf, cmd->stream);
			if (st)
				return;
		}
	}

	if (unlikely(card->eeh_state))
		return;

	/* Setting the valid bit will kick off the command. */
	iowrite32(cmd->op, card->regmap + CREG_CMD);
}