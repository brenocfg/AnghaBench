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
typedef  int /*<<< orphan*/  uint64_t ;
struct sq_gather_subdesc {int size; int /*<<< orphan*/  addr; int /*<<< orphan*/  ld_type; int /*<<< orphan*/  subdesc_type; } ;
struct TYPE_2__ {int q_len; } ;
struct snd_queue {TYPE_1__ dmem; } ;

/* Variables and functions */
 scalar_t__ GET_SQ_DESC (struct snd_queue*,int) ; 
 int /*<<< orphan*/  NIC_SEND_LD_TYPE_E_LDD ; 
 int /*<<< orphan*/  SND_QUEUE_DESC_SIZE ; 
 int /*<<< orphan*/  SQ_DESC_TYPE_GATHER ; 
 int /*<<< orphan*/  memset (struct sq_gather_subdesc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void nicvf_sq_add_gather_subdesc(struct snd_queue *sq, int qentry,
					       int size, uint64_t data)
{
	struct sq_gather_subdesc *gather;

	qentry &= (sq->dmem.q_len - 1);
	gather = (struct sq_gather_subdesc *)GET_SQ_DESC(sq, qentry);

	memset(gather, 0, SND_QUEUE_DESC_SIZE);
	gather->subdesc_type = SQ_DESC_TYPE_GATHER;
	gather->ld_type = NIC_SEND_LD_TYPE_E_LDD;
	gather->size = size;
	gather->addr = data;
}