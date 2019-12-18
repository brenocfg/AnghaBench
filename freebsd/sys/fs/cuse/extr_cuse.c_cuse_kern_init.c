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

/* Variables and functions */
 int CUSE_VERSION ; 
 int /*<<< orphan*/  GID_OPERATOR ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  cuse_dev ; 
 int /*<<< orphan*/  cuse_mtx ; 
 int /*<<< orphan*/  cuse_server_devsw ; 
 int /*<<< orphan*/  cuse_server_head ; 
 int /*<<< orphan*/  make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

__attribute__((used)) static void
cuse_kern_init(void *arg)
{
	TAILQ_INIT(&cuse_server_head);

	mtx_init(&cuse_mtx, "cuse-mtx", NULL, MTX_DEF);

	cuse_dev = make_dev(&cuse_server_devsw, 0,
	    UID_ROOT, GID_OPERATOR, 0600, "cuse");

	printf("Cuse v%d.%d.%d @ /dev/cuse\n",
	    (CUSE_VERSION >> 16) & 0xFF, (CUSE_VERSION >> 8) & 0xFF,
	    (CUSE_VERSION >> 0) & 0xFF);
}