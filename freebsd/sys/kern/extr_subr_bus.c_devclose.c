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
struct thread {int dummy; } ;
struct cdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtx; int /*<<< orphan*/  sigio; int /*<<< orphan*/  cv; scalar_t__ async; scalar_t__ nonblock; scalar_t__ inuse; } ;

/* Variables and functions */
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 TYPE_1__ devsoftc ; 
 int /*<<< orphan*/  funsetown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
devclose(struct cdev *dev, int fflag, int devtype, struct thread *td)
{

	mtx_lock(&devsoftc.mtx);
	devsoftc.inuse = 0;
	devsoftc.nonblock = 0;
	devsoftc.async = 0;
	cv_broadcast(&devsoftc.cv);
	funsetown(&devsoftc.sigio);
	mtx_unlock(&devsoftc.mtx);
	return (0);
}