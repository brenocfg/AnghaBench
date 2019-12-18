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
struct ibv_create_comp_channel_resp {int /*<<< orphan*/  fd; } ;
struct ibv_create_comp_channel {int dummy; } ;
struct ibv_context {int /*<<< orphan*/  cmd_fd; } ;
struct ibv_comp_channel {scalar_t__ refcnt; int /*<<< orphan*/  fd; struct ibv_context* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_COMP_CHANNEL ; 
 int /*<<< orphan*/  IBV_INIT_CMD_RESP (struct ibv_create_comp_channel*,int,int /*<<< orphan*/ ,struct ibv_create_comp_channel_resp*,int) ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (struct ibv_create_comp_channel_resp*,int) ; 
 int abi_ver ; 
 int /*<<< orphan*/  free (struct ibv_comp_channel*) ; 
 struct ibv_comp_channel* ibv_create_comp_channel_v2 (struct ibv_context*) ; 
 struct ibv_comp_channel* malloc (int) ; 
 int write (int /*<<< orphan*/ ,struct ibv_create_comp_channel*,int) ; 

struct ibv_comp_channel *ibv_create_comp_channel(struct ibv_context *context)
{
	struct ibv_comp_channel            *channel;
	struct ibv_create_comp_channel      cmd;
	struct ibv_create_comp_channel_resp resp;

	if (abi_ver <= 2)
		return ibv_create_comp_channel_v2(context);

	channel = malloc(sizeof *channel);
	if (!channel)
		return NULL;

	IBV_INIT_CMD_RESP(&cmd, sizeof cmd, CREATE_COMP_CHANNEL, &resp, sizeof resp);
	if (write(context->cmd_fd, &cmd, sizeof cmd) != sizeof cmd) {
		free(channel);
		return NULL;
	}

	(void) VALGRIND_MAKE_MEM_DEFINED(&resp, sizeof resp);

	channel->context = context;
	channel->fd      = resp.fd;
	channel->refcnt  = 0;

	return channel;
}