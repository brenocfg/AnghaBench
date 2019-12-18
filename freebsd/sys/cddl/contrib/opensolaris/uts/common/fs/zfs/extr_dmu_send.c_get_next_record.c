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
struct send_block_record {int dummy; } ;
typedef  int /*<<< orphan*/  bqueue_t ;

/* Variables and functions */
 struct send_block_record* bqueue_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (struct send_block_record*,int) ; 

__attribute__((used)) static struct send_block_record *
get_next_record(bqueue_t *bq, struct send_block_record *data)
{
	struct send_block_record *tmp = bqueue_dequeue(bq);
	kmem_free(data, sizeof (*data));
	return (tmp);
}