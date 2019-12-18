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
struct sp_device {int ord; int /*<<< orphan*/  axcache; struct device* dev; } ;
struct device {int dummy; } ;
struct ccp_device {int /*<<< orphan*/  rngname; int /*<<< orphan*/  name; int /*<<< orphan*/  suspend_queue; int /*<<< orphan*/  sb_queue; scalar_t__ sb_start; int /*<<< orphan*/  sb_count; int /*<<< orphan*/  sb_mutex; int /*<<< orphan*/  req_mutex; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  backlog; int /*<<< orphan*/  cmd; int /*<<< orphan*/  axcache; struct sp_device* sp; struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KSB_COUNT ; 
 int /*<<< orphan*/  MAX_CCP_NAME_LEN ; 
 struct ccp_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct ccp_device *ccp_alloc_struct(struct sp_device *sp)
{
	struct device *dev = sp->dev;
	struct ccp_device *ccp;

	ccp = devm_kzalloc(dev, sizeof(*ccp), GFP_KERNEL);
	if (!ccp)
		return NULL;
	ccp->dev = dev;
	ccp->sp = sp;
	ccp->axcache = sp->axcache;

	INIT_LIST_HEAD(&ccp->cmd);
	INIT_LIST_HEAD(&ccp->backlog);

	spin_lock_init(&ccp->cmd_lock);
	mutex_init(&ccp->req_mutex);
	mutex_init(&ccp->sb_mutex);
	ccp->sb_count = KSB_COUNT;
	ccp->sb_start = 0;

	/* Initialize the wait queues */
	init_waitqueue_head(&ccp->sb_queue);
	init_waitqueue_head(&ccp->suspend_queue);

	snprintf(ccp->name, MAX_CCP_NAME_LEN, "ccp-%u", sp->ord);
	snprintf(ccp->rngname, MAX_CCP_NAME_LEN, "ccp-%u-rng", sp->ord);

	return ccp;
}