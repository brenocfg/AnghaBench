#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_3__ {int idle_timeout; } ;
struct TYPE_4__ {TYPE_1__ transport_params; } ;

/* Variables and functions */
 TYPE_2__ quic_ctx ; 
 int /*<<< orphan*/  subtest (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bidirectional ; 
 int /*<<< orphan*/  test_downstream ; 
 int /*<<< orphan*/  test_even ; 

void test_loss(void)
{
    subtest("even", test_even);

    uint64_t idle_timeout_backup = quic_ctx.transport_params.idle_timeout;
    quic_ctx.transport_params.idle_timeout = (uint64_t)300 * 1000; /* 30 seconds */
    subtest("downstream", test_downstream);
    quic_ctx.transport_params.idle_timeout = (uint64_t)300 * 1000; /* 30 seconds */
    subtest("bidirectional", test_bidirectional);
    quic_ctx.transport_params.idle_timeout = idle_timeout_backup;
}