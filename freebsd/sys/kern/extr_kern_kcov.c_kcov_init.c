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
struct make_dev_args {int mda_mode; int /*<<< orphan*/  mda_gid; int /*<<< orphan*/  mda_uid; int /*<<< orphan*/ * mda_devsw; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  kcov_cdevsw ; 
 int /*<<< orphan*/  kcov_lock ; 
 int /*<<< orphan*/  kcov_thread_dtor ; 
 int /*<<< orphan*/  make_dev_args_init (struct make_dev_args*) ; 
 scalar_t__ make_dev_s (struct make_dev_args*,struct cdev**,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  thread_dtor ; 

__attribute__((used)) static void
kcov_init(const void *unused)
{
	struct make_dev_args args;
	struct cdev *dev;

	mtx_init(&kcov_lock, "kcov lock", NULL, MTX_SPIN);

	make_dev_args_init(&args);
	args.mda_devsw = &kcov_cdevsw;
	args.mda_uid = UID_ROOT;
	args.mda_gid = GID_WHEEL;
	args.mda_mode = 0600;
	if (make_dev_s(&args, &dev, "kcov") != 0) {
		printf("%s", "Failed to create kcov device");
		return;
	}

	EVENTHANDLER_REGISTER(thread_dtor, kcov_thread_dtor, NULL,
	    EVENTHANDLER_PRI_ANY);
}