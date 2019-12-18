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
struct spu_gang {int /*<<< orphan*/  aff_list_head; int /*<<< orphan*/  list; int /*<<< orphan*/  aff_mutex; int /*<<< orphan*/  mutex; int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct spu_gang* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct spu_gang *alloc_spu_gang(void)
{
	struct spu_gang *gang;

	gang = kzalloc(sizeof *gang, GFP_KERNEL);
	if (!gang)
		goto out;

	kref_init(&gang->kref);
	mutex_init(&gang->mutex);
	mutex_init(&gang->aff_mutex);
	INIT_LIST_HEAD(&gang->list);
	INIT_LIST_HEAD(&gang->aff_list_head);

out:
	return gang;
}