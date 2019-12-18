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
struct nl_sock {int dummy; } ;
struct nl_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_CMD_GETFAMILY ; 
 int /*<<< orphan*/  CTRL_VERSION ; 
 int /*<<< orphan*/  GENL_ID_CTRL ; 
 int /*<<< orphan*/  NLM_F_DUMP ; 
 int genl_send_simple (struct nl_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ctrl_request_update(struct nl_cache *c, struct nl_sock *h)
{
	return genl_send_simple(h, GENL_ID_CTRL, CTRL_CMD_GETFAMILY,
				CTRL_VERSION, NLM_F_DUMP);
}