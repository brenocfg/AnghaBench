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
struct mq_attr {int dummy; } ;
struct __mq {int oshandle; int /*<<< orphan*/ * node; } ;
typedef  struct __mq* mqd_t ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int __sys_kmq_open (char const*,int,int /*<<< orphan*/ ,struct mq_attr const*) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct __mq*) ; 
 struct __mq* malloc (int) ; 

mqd_t
__mq_open(const char *name, int oflag, mode_t mode,
	const struct mq_attr *attr)
{
	struct __mq *mq;
	int err;

	mq = malloc(sizeof(struct __mq));
	if (mq == NULL)
		return (NULL);

	mq->oshandle = __sys_kmq_open(name, oflag, mode, attr);
	if (mq->oshandle != -1) {
		mq->node = NULL;
		return (mq);
	}
	err = errno;
	free(mq);
	errno = err;
	return ((mqd_t)-1L);
}