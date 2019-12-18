#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5e_flow_table {size_t num_groups; int /*<<< orphan*/ ** g; int /*<<< orphan*/  t; } ;
struct TYPE_2__ {int /*<<< orphan*/  ethertype; int /*<<< orphan*/  ip_protocol; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ MLX5E_INNER_RSS_GROUP0_SIZE ; 
 scalar_t__ MLX5E_INNER_RSS_GROUP1_SIZE ; 
 scalar_t__ MLX5E_INNER_RSS_GROUP2_SIZE ; 
 int /*<<< orphan*/ * MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_MATCH_INNER_HEADERS ; 
 int /*<<< orphan*/  MLX5_SET_CFG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5_SET_TO_ONES (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_flow_group_in ; 
 int /*<<< orphan*/  end_flow_index ; 
 int /*<<< orphan*/  fte_match_param ; 
 TYPE_1__ inner_headers ; 
 int /*<<< orphan*/  match_criteria ; 
 int /*<<< orphan*/  match_criteria_enable ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* mlx5_create_flow_group (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_destroy_groups (struct mlx5e_flow_table*) ; 
 int /*<<< orphan*/  start_flow_index ; 

__attribute__((used)) static int
mlx5e_create_inner_rss_groups_sub(struct mlx5e_flow_table *ft, u32 *in,
					   int inlen)
{
	u8 *mc = MLX5_ADDR_OF(create_flow_group_in, in, match_criteria);
	int err;
	int ix = 0;

	memset(in, 0, inlen);
	MLX5_SET_CFG(in, match_criteria_enable, MLX5_MATCH_INNER_HEADERS);
	MLX5_SET_TO_ONES(fte_match_param, mc, inner_headers.ethertype);
	MLX5_SET_TO_ONES(fte_match_param, mc, inner_headers.ip_protocol);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_INNER_RSS_GROUP0_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	if (IS_ERR(ft->g[ft->num_groups]))
		goto err_destory_groups;
	ft->num_groups++;

	memset(in, 0, inlen);
	MLX5_SET_CFG(in, match_criteria_enable, MLX5_MATCH_INNER_HEADERS);
	MLX5_SET_TO_ONES(fte_match_param, mc, inner_headers.ethertype);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_INNER_RSS_GROUP1_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	if (IS_ERR(ft->g[ft->num_groups]))
		goto err_destory_groups;
	ft->num_groups++;

	memset(in, 0, inlen);
	MLX5_SET_CFG(in, start_flow_index, ix);
	ix += MLX5E_INNER_RSS_GROUP2_SIZE;
	MLX5_SET_CFG(in, end_flow_index, ix - 1);
	ft->g[ft->num_groups] = mlx5_create_flow_group(ft->t, in);
	if (IS_ERR(ft->g[ft->num_groups]))
		goto err_destory_groups;
	ft->num_groups++;

	return (0);

err_destory_groups:
	err = PTR_ERR(ft->g[ft->num_groups]);
	ft->g[ft->num_groups] = NULL;
	mlx5e_destroy_groups(ft);

	return (err);
}