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
struct cn_queue_dev {int /*<<< orphan*/  refcnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct cn_callback_entry {void (* callback ) (struct cn_msg*,struct netlink_skb_parms*) ;TYPE_1__ id; struct cn_queue_dev* pdev; int /*<<< orphan*/  refcnt; } ;
struct cb_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct cn_callback_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct cb_id*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 

__attribute__((used)) static struct cn_callback_entry *
cn_queue_alloc_callback_entry(struct cn_queue_dev *dev, const char *name,
			      struct cb_id *id,
			      void (*callback)(struct cn_msg *,
					       struct netlink_skb_parms *))
{
	struct cn_callback_entry *cbq;

	cbq = kzalloc(sizeof(*cbq), GFP_KERNEL);
	if (!cbq) {
		pr_err("Failed to create new callback queue.\n");
		return NULL;
	}

	refcount_set(&cbq->refcnt, 1);

	atomic_inc(&dev->refcnt);
	cbq->pdev = dev;

	snprintf(cbq->id.name, sizeof(cbq->id.name), "%s", name);
	memcpy(&cbq->id.id, id, sizeof(struct cb_id));
	cbq->callback = callback;
	return cbq;
}