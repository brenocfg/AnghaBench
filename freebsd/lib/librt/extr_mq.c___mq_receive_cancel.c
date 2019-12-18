#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
typedef  TYPE_1__* mqd_t ;
struct TYPE_3__ {int /*<<< orphan*/  oshandle; } ;

/* Variables and functions */
 int __sys_kmq_timedreceive (int /*<<< orphan*/ ,char*,size_t,unsigned int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _pthread_cancel_enter (int) ; 
 int /*<<< orphan*/  _pthread_cancel_leave (int) ; 

ssize_t
__mq_receive_cancel(mqd_t mqd, char *buf, size_t len, unsigned *prio)
{
	int ret;

	_pthread_cancel_enter(1);
	ret = __sys_kmq_timedreceive(mqd->oshandle, buf, len, prio, NULL);
	_pthread_cancel_leave(ret == -1);
	return (ret);
}