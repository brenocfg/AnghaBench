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
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GID_WHEEL ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_dev_args_init (struct make_dev_args*) ; 
 int make_dev_s (struct make_dev_args*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  my_devsw ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sdev ; 

__attribute__((used)) static int
cdev_load(module_t mod, int cmd, void *arg)
{
    int  err = 0;
    struct make_dev_args mda;

    switch (cmd) {
    case MOD_LOAD:
	
	/* Do any initialization that you should do with the kernel */
	
	/* if we make it to here, print copyright on console*/
	printf("\nSample Loaded kld character device driver\n");
	printf("Copyright (c) 1998\n");
	printf("Rajesh Vaidheeswarran\n");
	printf("All rights reserved\n");

	make_dev_args_init(&mda);
	mda.mda_devsw = &my_devsw;
	mda.mda_uid = UID_ROOT;
	mda.mda_gid = GID_WHEEL;
	mda.mda_mode = 0600;
	err = make_dev_s(&mda, &sdev, "cdev");
	break;

    case MOD_UNLOAD:
	printf("Unloaded kld character device driver\n");
	destroy_dev(sdev);
	break;		/* Success*/

    default:	/* we only understand load/unload*/
	err = EOPNOTSUPP;
	break;
    }

    return(err);
}