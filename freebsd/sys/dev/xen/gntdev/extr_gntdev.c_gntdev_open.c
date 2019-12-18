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
struct thread {int dummy; } ;
struct per_user_data {int /*<<< orphan*/  user_data_lock; int /*<<< orphan*/  file_offset; int /*<<< orphan*/  gmap_tree; int /*<<< orphan*/  gref_tree; } ;
struct file_offset_struct {int /*<<< orphan*/  count; scalar_t__ file_offset; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_OFFSET_COUNT ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_GNTDEV ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct file_offset_struct*) ; 
 int devfs_set_cdevpriv (struct per_user_data*,int /*<<< orphan*/  (*) (struct per_user_data*)) ; 
 int /*<<< orphan*/  file_offset_head ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  per_user_data_dtor (struct per_user_data*) ; 

__attribute__((used)) static int
gntdev_open(struct cdev *dev, int flag, int otyp, struct thread *td)
{
	int error;
	struct per_user_data *priv_user;
	struct file_offset_struct *offset;

	priv_user = malloc(sizeof(*priv_user), M_GNTDEV, M_WAITOK | M_ZERO);
	RB_INIT(&priv_user->gref_tree);
	RB_INIT(&priv_user->gmap_tree);
	RB_INIT(&priv_user->file_offset);
	offset = malloc(sizeof(*offset), M_GNTDEV, M_WAITOK | M_ZERO);
	offset->file_offset = 0;
	offset->count = MAX_OFFSET_COUNT;
	RB_INSERT(file_offset_head, &priv_user->file_offset, offset);
	mtx_init(&priv_user->user_data_lock,
	    "per user data mutex", NULL, MTX_DEF);

	error = devfs_set_cdevpriv(priv_user, per_user_data_dtor);
	if (error != 0)
		per_user_data_dtor(priv_user);

	return (error);
}