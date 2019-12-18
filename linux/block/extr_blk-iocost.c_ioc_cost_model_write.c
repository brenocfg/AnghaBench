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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u ;
typedef  int /*<<< orphan*/  substring_t ;
struct kernfs_open_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * i_lcoefs; } ;
struct ioc {int user_cost_model; int /*<<< orphan*/  lock; TYPE_1__ params; } ;
struct gendisk {int /*<<< orphan*/  queue; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  COST_CTRL 129 
#define  COST_MODEL 128 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct gendisk*) ; 
 int MAX_OPT_ARGS ; 
 int NR_I_LCOEFS ; 
 size_t PTR_ERR (struct gendisk*) ; 
 int blk_iocost_init (int /*<<< orphan*/ ) ; 
 struct gendisk* blkcg_conf_get_disk (char**) ; 
 int /*<<< orphan*/  cost_ctrl_tokens ; 
 int /*<<< orphan*/  i_lcoef_tokens ; 
 int /*<<< orphan*/  ioc_refresh_params (struct ioc*,int) ; 
 int /*<<< orphan*/  match_strlcpy (char*,int /*<<< orphan*/ *,int) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ match_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_disk_and_module (struct gendisk*) ; 
 struct ioc* q_to_ioc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static ssize_t ioc_cost_model_write(struct kernfs_open_file *of, char *input,
				    size_t nbytes, loff_t off)
{
	struct gendisk *disk;
	struct ioc *ioc;
	u64 u[NR_I_LCOEFS];
	bool user;
	char *p;
	int ret;

	disk = blkcg_conf_get_disk(&input);
	if (IS_ERR(disk))
		return PTR_ERR(disk);

	ioc = q_to_ioc(disk->queue);
	if (!ioc) {
		ret = blk_iocost_init(disk->queue);
		if (ret)
			goto err;
		ioc = q_to_ioc(disk->queue);
	}

	spin_lock_irq(&ioc->lock);
	memcpy(u, ioc->params.i_lcoefs, sizeof(u));
	user = ioc->user_cost_model;
	spin_unlock_irq(&ioc->lock);

	while ((p = strsep(&input, " \t\n"))) {
		substring_t args[MAX_OPT_ARGS];
		char buf[32];
		int tok;
		u64 v;

		if (!*p)
			continue;

		switch (match_token(p, cost_ctrl_tokens, args)) {
		case COST_CTRL:
			match_strlcpy(buf, &args[0], sizeof(buf));
			if (!strcmp(buf, "auto"))
				user = false;
			else if (!strcmp(buf, "user"))
				user = true;
			else
				goto einval;
			continue;
		case COST_MODEL:
			match_strlcpy(buf, &args[0], sizeof(buf));
			if (strcmp(buf, "linear"))
				goto einval;
			continue;
		}

		tok = match_token(p, i_lcoef_tokens, args);
		if (tok == NR_I_LCOEFS)
			goto einval;
		if (match_u64(&args[0], &v))
			goto einval;
		u[tok] = v;
		user = true;
	}

	spin_lock_irq(&ioc->lock);
	if (user) {
		memcpy(ioc->params.i_lcoefs, u, sizeof(u));
		ioc->user_cost_model = true;
	} else {
		ioc->user_cost_model = false;
	}
	ioc_refresh_params(ioc, true);
	spin_unlock_irq(&ioc->lock);

	put_disk_and_module(disk);
	return nbytes;

einval:
	ret = -EINVAL;
err:
	put_disk_and_module(disk);
	return ret;
}