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
struct somemem {int /*<<< orphan*/  mutexetum; } ;
typedef  int /*<<< orphan*/  krwlock_t ;
typedef  int /*<<< orphan*/  kmutex_t ;
typedef  enum locktest { ____Placeholder_locktest } locktest ;

/* Variables and functions */
 int /*<<< orphan*/  IPL_NONE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
#define  LOCKME_DESTROYHELD 135 
#define  LOCKME_DOUBLEFREE 134 
#define  LOCKME_DOUBLEINIT 133 
#define  LOCKME_MEMFREE 132 
#define  LOCKME_MTX 131 
#define  LOCKME_RWDOUBLEX 130 
#define  LOCKME_RWRX 129 
#define  LOCKME_RWXR 128 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  RW_WRITER ; 
 struct somemem* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (struct somemem*,int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_init (int /*<<< orphan*/ *) ; 

void
rumptest_lockme(enum locktest what)
{
	struct somemem *some;
	kmutex_t mtx;
	krwlock_t rw;

	rw_init(&rw);
	mutex_init(&mtx, MUTEX_DEFAULT, IPL_NONE);

	switch (what) {
	case LOCKME_MTX:
		mutex_enter(&mtx);
		mutex_enter(&mtx);
		break;
	case LOCKME_RWDOUBLEX:
		rw_enter(&rw, RW_WRITER);
		rw_enter(&rw, RW_WRITER);
		break;
	case LOCKME_RWRX:
		rw_enter(&rw, RW_READER);
		rw_enter(&rw, RW_WRITER);
		break;
	case LOCKME_RWXR:
		rw_enter(&rw, RW_WRITER);
		rw_enter(&rw, RW_READER);
		break;
	case LOCKME_DOUBLEINIT:
		mutex_init(&mtx, MUTEX_DEFAULT, IPL_NONE);
		break;
	case LOCKME_DOUBLEFREE:
		mutex_destroy(&mtx);
		mutex_destroy(&mtx);
		break;
	case LOCKME_DESTROYHELD:
		mutex_enter(&mtx);
		mutex_destroy(&mtx);
		break;
	case LOCKME_MEMFREE:
		some = kmem_alloc(sizeof(*some), KM_SLEEP);
		mutex_init(&some->mutexetum, MUTEX_DEFAULT, IPL_NONE);
		kmem_free(some, sizeof(*some));
		break;
	}
}