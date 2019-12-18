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
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_flow_table {int dummy; } ;
struct mlx5_flow_namespace {int dummy; } ;

/* Variables and functions */
 struct mlx5_flow_table* create_ft_common (struct mlx5_flow_namespace*,int /*<<< orphan*/ ,int,int,char const*) ; 

struct mlx5_flow_table *mlx5_create_vport_flow_table(struct mlx5_flow_namespace *ns,
						     u16 vport,
						     int prio,
						     const char *name,
						     int num_flow_table_entries)
{
	return create_ft_common(ns, vport, prio, num_flow_table_entries, name);
}