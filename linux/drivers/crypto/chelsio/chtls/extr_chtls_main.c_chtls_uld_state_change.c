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
struct TYPE_2__ {int /*<<< orphan*/  release; int /*<<< orphan*/  kref; } ;
struct chtls_dev {TYPE_1__ tlsdev; int /*<<< orphan*/  list; } ;
typedef  enum cxgb4_state { ____Placeholder_cxgb4_state } cxgb4_state ;

/* Variables and functions */
#define  CXGB4_STATE_DETACH 131 
#define  CXGB4_STATE_DOWN 130 
#define  CXGB4_STATE_START_RECOVERY 129 
#define  CXGB4_STATE_UP 128 
 int /*<<< orphan*/  cdev_mutex ; 
 int /*<<< orphan*/  chtls_register_dev (struct chtls_dev*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int chtls_uld_state_change(void *handle, enum cxgb4_state new_state)
{
	struct chtls_dev *cdev = handle;

	switch (new_state) {
	case CXGB4_STATE_UP:
		chtls_register_dev(cdev);
		break;
	case CXGB4_STATE_DOWN:
		break;
	case CXGB4_STATE_START_RECOVERY:
		break;
	case CXGB4_STATE_DETACH:
		mutex_lock(&cdev_mutex);
		list_del(&cdev->list);
		mutex_unlock(&cdev_mutex);
		kref_put(&cdev->tlsdev.kref, cdev->tlsdev.release);
		break;
	default:
		break;
	}
	return 0;
}