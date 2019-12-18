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
typedef  void* u32 ;
struct queue {int dummy; } ;
struct fs_dev {int dummy; } ;
struct FS_QENTRY {void* p2; void* p1; void* p0; void* cmd; } ;
struct TYPE_2__ {void* p2; void* p1; void* p0; void* cmd; } ;

/* Variables and functions */
 struct FS_QENTRY* get_qentry (struct fs_dev*,struct queue*) ; 
 TYPE_1__* pq ; 
 size_t qp ; 
 int /*<<< orphan*/  submit_qentry (struct fs_dev*,struct queue*,struct FS_QENTRY*) ; 

__attribute__((used)) static void submit_queue (struct fs_dev *dev, struct queue *q, 
			  u32 cmd, u32 p1, u32 p2, u32 p3)
{
	struct FS_QENTRY *qe;

	qe = get_qentry (dev, q);
	qe->cmd = cmd;
	qe->p0 = p1;
	qe->p1 = p2;
	qe->p2 = p3;
	submit_qentry (dev,  q, qe);

#ifdef DEBUG_EXTRA
	pq[qp].cmd = cmd;
	pq[qp].p0 = p1;
	pq[qp].p1 = p2;
	pq[qp].p2 = p3;
	qp++;
	if (qp >= 60) qp = 0;
#endif
}