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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct mlx5_flow_group* fte; struct mlx5_flow_group* fg; } ;
struct mlx5_flow_table {int /*<<< orphan*/  id; int /*<<< orphan*/  type; int /*<<< orphan*/  vport; int /*<<< orphan*/  base; TYPE_1__ star_rule; int /*<<< orphan*/  max_fte; } ;
struct mlx5_flow_root_namespace {int /*<<< orphan*/  fs_chain_lock; int /*<<< orphan*/  dev; } ;
struct mlx5_flow_group {int /*<<< orphan*/  id; } ;
struct fs_prio {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct mlx5_flow_group*) ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct mlx5_flow_group*) ; 
 struct mlx5_flow_group* alloc_star_ft_entry (struct mlx5_flow_table*,struct mlx5_flow_group*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int connect_prev_fts (int /*<<< orphan*/ *,struct fs_prio*,struct mlx5_flow_table*) ; 
 int /*<<< orphan*/  create_flow_group_in ; 
 int /*<<< orphan*/  end_flow_index ; 
 struct mlx5_flow_table* find_next_ft (struct fs_prio*) ; 
 struct mlx5_flow_table* find_prev_ft (struct mlx5_flow_table*,struct fs_prio*) ; 
 struct mlx5_flow_root_namespace* find_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_star_fte_entry (struct mlx5_flow_group*) ; 
 struct mlx5_flow_group* fs_alloc_fg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs_get_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs_get_parent (struct fs_prio*,struct mlx5_flow_table*) ; 
 int /*<<< orphan*/  fs_put (int /*<<< orphan*/ *) ; 
 int fs_set_star_rule (int /*<<< orphan*/ ,struct mlx5_flow_table*,struct mlx5_flow_table*) ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/  kfree (struct mlx5_flow_group*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int mlx5_cmd_fs_create_fg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_cmd_fs_destroy_fg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * mlx5_vzalloc (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_flow_index ; 

__attribute__((used)) static int create_star_rule(struct mlx5_flow_table *ft, struct fs_prio *prio)
{
	struct mlx5_flow_group *fg;
	int err;
	u32 *fg_in;
	u32 *match_value;
	struct mlx5_flow_table *next_ft;
	struct mlx5_flow_table *prev_ft;
	struct mlx5_flow_root_namespace *root = find_root(&prio->base);
	int fg_inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	int match_len = MLX5_ST_SZ_BYTES(fte_match_param);

	fg_in = mlx5_vzalloc(fg_inlen);
	if (!fg_in) {
		mlx5_core_warn(root->dev, "failed to allocate inbox\n");
		return -ENOMEM;
	}

	match_value = mlx5_vzalloc(match_len);
	if (!match_value) {
		mlx5_core_warn(root->dev, "failed to allocate inbox\n");
		kvfree(fg_in);
		return -ENOMEM;
	}

	MLX5_SET(create_flow_group_in, fg_in, start_flow_index, ft->max_fte);
	MLX5_SET(create_flow_group_in, fg_in, end_flow_index, ft->max_fte);
	fg = fs_alloc_fg(fg_in);
	if (IS_ERR(fg)) {
		err = PTR_ERR(fg);
		goto out;
	}
	ft->star_rule.fg = fg;
	err =  mlx5_cmd_fs_create_fg(fs_get_dev(&prio->base),
				     fg_in, ft->vport, ft->type,
				     ft->id,
				     &fg->id);
	if (err)
		goto free_fg;

	ft->star_rule.fte = alloc_star_ft_entry(ft, fg,
						      match_value,
						      ft->max_fte);
	if (IS_ERR(ft->star_rule.fte))
		goto free_star_rule;

	mutex_lock(&root->fs_chain_lock);
	next_ft = find_next_ft(prio);
	err = fs_set_star_rule(root->dev, ft, next_ft);
	if (err) {
		mutex_unlock(&root->fs_chain_lock);
		goto free_star_rule;
	}
	if (next_ft) {
		struct fs_prio *parent;

		fs_get_parent(parent, next_ft);
		fs_put(&next_ft->base);
	}
	prev_ft = find_prev_ft(ft, prio);
	if (prev_ft) {
		struct fs_prio *prev_parent;

		fs_get_parent(prev_parent, prev_ft);

		err = connect_prev_fts(NULL, prev_parent, ft);
		if (err) {
			mutex_unlock(&root->fs_chain_lock);
			goto destroy_chained_star_rule;
		}
		fs_put(&prev_ft->base);
	}
	mutex_unlock(&root->fs_chain_lock);
	kvfree(fg_in);
	kvfree(match_value);

	return 0;

destroy_chained_star_rule:
	fs_set_star_rule(fs_get_dev(&prio->base), ft, NULL);
	if (next_ft)
		fs_put(&next_ft->base);
free_star_rule:
	free_star_fte_entry(ft->star_rule.fte);
	mlx5_cmd_fs_destroy_fg(fs_get_dev(&ft->base), ft->vport,
			       ft->type, ft->id,
			       fg->id);
free_fg:
	kfree(fg);
out:
	kvfree(fg_in);
	kvfree(match_value);
	return err;
}