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
struct mlx5_flow_rule_node {int match_criteria_enable; int /*<<< orphan*/  list; int /*<<< orphan*/  match_value; int /*<<< orphan*/  match_criteria; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IPPROTO_UDP ; 
 int MLX5_CREATE_FLOW_GROUP_IN_MATCH_CRITERIA_ENABLE_OUTER_HEADERS ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ROCEV2_UDP_PORT ; 
 int /*<<< orphan*/  ethertype ; 
 int /*<<< orphan*/  fte_match_set_lyr_2_4 ; 
 int /*<<< orphan*/  ip_protocol ; 
 int /*<<< orphan*/  kfree (struct mlx5_flow_rule_node*) ; 
 struct mlx5_flow_rule_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  udp_dport ; 

__attribute__((used)) static int set_rocev2_rules(struct list_head *rules_list)
{
	struct mlx5_flow_rule_node *ipv4_rule;
	struct mlx5_flow_rule_node *ipv6_rule;

	ipv4_rule = kzalloc(sizeof(*ipv4_rule), GFP_KERNEL);
	if (!ipv4_rule)
		return -ENOMEM;

	ipv6_rule = kzalloc(sizeof(*ipv6_rule), GFP_KERNEL);
	if (!ipv6_rule) {
		kfree(ipv4_rule);
		return -ENOMEM;
	}

	ipv4_rule->match_criteria_enable =
		1 << MLX5_CREATE_FLOW_GROUP_IN_MATCH_CRITERIA_ENABLE_OUTER_HEADERS;
	MLX5_SET(fte_match_set_lyr_2_4, ipv4_rule->match_criteria, ethertype,
		 0xffff);
	MLX5_SET(fte_match_set_lyr_2_4, ipv4_rule->match_value, ethertype,
		 0x0800);
	MLX5_SET(fte_match_set_lyr_2_4, ipv4_rule->match_criteria, ip_protocol,
		 0xff);
	MLX5_SET(fte_match_set_lyr_2_4, ipv4_rule->match_value, ip_protocol,
		 IPPROTO_UDP);
	MLX5_SET(fte_match_set_lyr_2_4, ipv4_rule->match_criteria, udp_dport,
		 0xffff);
	MLX5_SET(fte_match_set_lyr_2_4, ipv4_rule->match_value, udp_dport,
		 ROCEV2_UDP_PORT);

	ipv6_rule->match_criteria_enable =
		1 << MLX5_CREATE_FLOW_GROUP_IN_MATCH_CRITERIA_ENABLE_OUTER_HEADERS;
	MLX5_SET(fte_match_set_lyr_2_4, ipv6_rule->match_criteria, ethertype,
		 0xffff);
	MLX5_SET(fte_match_set_lyr_2_4, ipv6_rule->match_value, ethertype,
		 0x86dd);
	MLX5_SET(fte_match_set_lyr_2_4, ipv6_rule->match_criteria, ip_protocol,
		 0xff);
	MLX5_SET(fte_match_set_lyr_2_4, ipv6_rule->match_value, ip_protocol,
		 IPPROTO_UDP);
	MLX5_SET(fte_match_set_lyr_2_4, ipv6_rule->match_criteria, udp_dport,
		 0xffff);
	MLX5_SET(fte_match_set_lyr_2_4, ipv6_rule->match_value, udp_dport,
		 ROCEV2_UDP_PORT);

	list_add_tail(&ipv4_rule->list, rules_list);
	list_add_tail(&ipv6_rule->list, rules_list);

	return 0;
}