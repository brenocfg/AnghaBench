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
struct sbitmap {int dummy; } ;
struct request {int dummy; } ;
struct bt_tags_iter_data {int reserved; int (* fn ) (struct request*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  data; struct blk_mq_tags* tags; } ;
struct blk_mq_tags {struct request** rqs; scalar_t__ nr_reserved_tags; } ;

/* Variables and functions */
 scalar_t__ blk_mq_request_started (struct request*) ; 
 int stub1 (struct request*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool bt_tags_iter(struct sbitmap *bitmap, unsigned int bitnr, void *data)
{
	struct bt_tags_iter_data *iter_data = data;
	struct blk_mq_tags *tags = iter_data->tags;
	bool reserved = iter_data->reserved;
	struct request *rq;

	if (!reserved)
		bitnr += tags->nr_reserved_tags;

	/*
	 * We can hit rq == NULL here, because the tagging functions
	 * test and set the bit before assining ->rqs[].
	 */
	rq = tags->rqs[bitnr];
	if (rq && blk_mq_request_started(rq))
		return iter_data->fn(rq, iter_data->data, reserved);

	return true;
}