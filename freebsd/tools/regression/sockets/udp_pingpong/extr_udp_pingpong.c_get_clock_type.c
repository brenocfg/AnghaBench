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
struct test_ctx {int ts_type; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
#define  TT_BINTIME 133 
#define  TT_MONOTONIC 132 
#define  TT_REALTIME 131 
#define  TT_REALTIME_MICRO 130 
#define  TT_TIMESTAMP 129 
#define  TT_TS_BINTIME 128 
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static clockid_t
get_clock_type(struct test_ctx *tcp)
{
    switch (tcp->ts_type) {
    case TT_TIMESTAMP:
    case TT_BINTIME:
    case TT_REALTIME_MICRO:
    case TT_TS_BINTIME:
    case TT_REALTIME:
        return (CLOCK_REALTIME);

    case TT_MONOTONIC:
        return (CLOCK_MONOTONIC);
    }
    abort();
}