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

/* Variables and functions */

int dtls1_get_queue_priority(unsigned short seq, int is_ccs)
{
    /*
     * The index of the retransmission queue actually is the message sequence
     * number, since the queue only contains messages of a single handshake.
     * However, the ChangeCipherSpec has no message sequence number and so
     * using only the sequence will result in the CCS and Finished having the
     * same index. To prevent this, the sequence number is multiplied by 2.
     * In case of a CCS 1 is subtracted. This does not only differ CSS and
     * Finished, it also maintains the order of the index (important for
     * priority queues) and fits in the unsigned short variable.
     */
    return seq * 2 - is_ccs;
}