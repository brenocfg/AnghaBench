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
struct qentry {int dummy; } ;

/* Variables and functions */
 struct qentry* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  queue ; 

__attribute__((used)) static struct qentry *
dequeue(void)
{
	struct qentry *item;

	item = STAILQ_FIRST(&queue);
	if (item == NULL)
		return (NULL);

	STAILQ_REMOVE_HEAD(&queue, list);
	--count;
	return (item);
}