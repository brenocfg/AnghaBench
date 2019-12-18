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
typedef  int /*<<< orphan*/  u32 ;
struct rsxx_cardinfo {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CREG_ADD_CARD_CMD ; 
 int rsxx_creg_write (struct rsxx_cardinfo*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int rsxx_issue_card_cmd(struct rsxx_cardinfo *card, u32 cmd)
{
	return rsxx_creg_write(card, CREG_ADD_CARD_CMD,
				   sizeof(cmd), &cmd, 0);
}