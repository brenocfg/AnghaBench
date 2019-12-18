#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  crc_error_count; int /*<<< orphan*/  invalid_transmission_word_error_count; int /*<<< orphan*/  primitive_sequence_error_count; int /*<<< orphan*/  loss_of_sync_error_count; int /*<<< orphan*/  link_failure_error_count; } ;
struct TYPE_7__ {int /*<<< orphan*/  semaphore; TYPE_1__ link_stats; } ;
struct TYPE_8__ {TYPE_2__ stats; } ;
typedef  TYPE_3__ ocs_xport_stats_t ;
struct TYPE_9__ {int /*<<< orphan*/  counter; } ;
typedef  TYPE_4__ ocs_hw_link_stat_counts_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 size_t OCS_HW_LINK_STAT_CRC_COUNT ; 
 size_t OCS_HW_LINK_STAT_INVALID_XMIT_WORD_COUNT ; 
 size_t OCS_HW_LINK_STAT_LINK_FAILURE_COUNT ; 
 size_t OCS_HW_LINK_STAT_LOSS_OF_SYNC_COUNT ; 
 size_t OCS_HW_LINK_STAT_PRIMITIVE_SEQ_COUNT ; 
 int /*<<< orphan*/  ocs_sem_v (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ocs_xport_link_stats_cb(int32_t status, uint32_t num_counters, ocs_hw_link_stat_counts_t *counters, void *arg)
{
        ocs_xport_stats_t *result = arg;

        result->stats.link_stats.link_failure_error_count = counters[OCS_HW_LINK_STAT_LINK_FAILURE_COUNT].counter;
        result->stats.link_stats.loss_of_sync_error_count = counters[OCS_HW_LINK_STAT_LOSS_OF_SYNC_COUNT].counter;
        result->stats.link_stats.primitive_sequence_error_count = counters[OCS_HW_LINK_STAT_PRIMITIVE_SEQ_COUNT].counter;
        result->stats.link_stats.invalid_transmission_word_error_count = counters[OCS_HW_LINK_STAT_INVALID_XMIT_WORD_COUNT].counter;
        result->stats.link_stats.crc_error_count = counters[OCS_HW_LINK_STAT_CRC_COUNT].counter;

        ocs_sem_v(&(result->stats.semaphore));
}