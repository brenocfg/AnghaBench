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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct my_nfattr {int dummy; } ;
typedef  int /*<<< orphan*/  pcap_t ;

/* Variables and functions */
 int NFNL_SUBSYS_ULOG ; 
 int NFULNL_MSG_CONFIG ; 
 int netfilter_send_config_msg (int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct my_nfattr const*) ; 

__attribute__((used)) static int
nflog_send_config_msg(const pcap_t *handle, uint8_t family, u_int16_t group_id, const struct my_nfattr *mynfa)
{
	return netfilter_send_config_msg(handle, (NFNL_SUBSYS_ULOG << 8) | NFULNL_MSG_CONFIG, 1, family, group_id, mynfa);
}