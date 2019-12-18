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
struct queue_pair_list {int /*<<< orphan*/  mutex; int /*<<< orphan*/  hibernate; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_store_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_list_init (int /*<<< orphan*/ *) ; 
 int vmci_mutex_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static inline int
queue_pair_list_init(struct queue_pair_list *qp_list)
{
	int ret;

	vmci_list_init(&qp_list->head);
	atomic_store_int(&qp_list->hibernate, 0);
	ret = vmci_mutex_init(&qp_list->mutex, "VMCI QP List lock");
	return (ret);
}