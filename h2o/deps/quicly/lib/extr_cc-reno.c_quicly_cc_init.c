#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cwnd; int /*<<< orphan*/  ssthresh; } ;
typedef  TYPE_1__ quicly_cc_t ;

/* Variables and functions */
 int QUICLY_INITIAL_WINDOW ; 
 int QUICLY_MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void quicly_cc_init(quicly_cc_t *cc)
{
    memset(cc, 0, sizeof(quicly_cc_t));
    cc->cwnd = QUICLY_INITIAL_WINDOW * QUICLY_MAX_PACKET_SIZE;
    cc->ssthresh = UINT32_MAX;
}