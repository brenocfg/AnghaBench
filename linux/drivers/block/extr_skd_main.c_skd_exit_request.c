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
struct skd_request_context {int /*<<< orphan*/  sksg_dma_address; int /*<<< orphan*/  sksg_list; } ;
struct skd_device {int dummy; } ;
struct request {int dummy; } ;
struct blk_mq_tag_set {struct skd_device* driver_data; } ;

/* Variables and functions */
 struct skd_request_context* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  skd_free_sg_list (struct skd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skd_exit_request(struct blk_mq_tag_set *set, struct request *rq,
			     unsigned int hctx_idx)
{
	struct skd_device *skdev = set->driver_data;
	struct skd_request_context *skreq = blk_mq_rq_to_pdu(rq);

	skd_free_sg_list(skdev, skreq->sksg_list, skreq->sksg_dma_address);
}