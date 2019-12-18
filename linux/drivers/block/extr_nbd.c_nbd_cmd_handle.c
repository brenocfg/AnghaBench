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
typedef  int u64 ;
typedef  int u32 ;
struct request {int dummy; } ;
struct nbd_cmd {int cmd_cookie; } ;

/* Variables and functions */
 int NBD_COOKIE_BITS ; 
 struct request* blk_mq_rq_from_pdu (struct nbd_cmd*) ; 
 int blk_mq_unique_tag (struct request*) ; 

__attribute__((used)) static u64 nbd_cmd_handle(struct nbd_cmd *cmd)
{
	struct request *req = blk_mq_rq_from_pdu(cmd);
	u32 tag = blk_mq_unique_tag(req);
	u64 cookie = cmd->cmd_cookie;

	return (cookie << NBD_COOKIE_BITS) | tag;
}