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
struct rq_qos {TYPE_1__* ops; void* debugfs_dir; struct request_queue* q; int /*<<< orphan*/  id; } ;
struct request_queue {void* rqos_debugfs_dir; void* debugfs_dir; } ;
struct TYPE_2__ {int /*<<< orphan*/  debugfs_attrs; } ;

/* Variables and functions */
 void* debugfs_create_dir (char const*,void*) ; 
 int /*<<< orphan*/  debugfs_create_files (void*,struct rq_qos*,int /*<<< orphan*/ ) ; 
 char* rq_qos_id_to_name (int /*<<< orphan*/ ) ; 

void blk_mq_debugfs_register_rqos(struct rq_qos *rqos)
{
	struct request_queue *q = rqos->q;
	const char *dir_name = rq_qos_id_to_name(rqos->id);

	if (rqos->debugfs_dir || !rqos->ops->debugfs_attrs)
		return;

	if (!q->rqos_debugfs_dir)
		q->rqos_debugfs_dir = debugfs_create_dir("rqos",
							 q->debugfs_dir);

	rqos->debugfs_dir = debugfs_create_dir(dir_name,
					       rqos->q->rqos_debugfs_dir);

	debugfs_create_files(rqos->debugfs_dir, rqos, rqos->ops->debugfs_attrs);
}