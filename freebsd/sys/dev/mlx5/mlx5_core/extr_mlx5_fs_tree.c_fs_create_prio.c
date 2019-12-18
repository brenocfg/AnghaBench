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
struct mlx5_flow_namespace {int /*<<< orphan*/  prios; int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; int /*<<< orphan*/  type; } ;
struct fs_prio {int max_ft; unsigned int prio; int /*<<< orphan*/  shared_lock; int /*<<< orphan*/  objs; TYPE_1__ base; int /*<<< orphan*/  flags; int /*<<< orphan*/  max_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct fs_prio* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_TYPE_PRIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLX5_CORE_FS_PRIO_MAX_NS ; 
 int /*<<< orphan*/  fs_add_node (TYPE_1__*,int /*<<< orphan*/ *,char const*,int) ; 
 struct fs_prio* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct fs_prio *fs_create_prio(struct mlx5_flow_namespace *ns,
				      unsigned prio, int max_ft,
				      const char *name, u8 flags)
{
	struct fs_prio *fs_prio;

	fs_prio = kzalloc(sizeof(*fs_prio), GFP_KERNEL);
	if (!fs_prio)
		return ERR_PTR(-ENOMEM);

	fs_prio->base.type = FS_TYPE_PRIO;
	fs_add_node(&fs_prio->base, &ns->base, name, 1);
	fs_prio->max_ft = max_ft;
	fs_prio->max_ns = MLX5_CORE_FS_PRIO_MAX_NS;
	fs_prio->prio = prio;
	fs_prio->flags = flags;
	list_add_tail(&fs_prio->base.list, &ns->prios);
	INIT_LIST_HEAD(&fs_prio->objs);
	mutex_init(&fs_prio->shared_lock);

	return fs_prio;
}