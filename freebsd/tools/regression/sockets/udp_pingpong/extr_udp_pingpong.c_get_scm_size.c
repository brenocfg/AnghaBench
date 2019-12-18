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
struct timeval {int dummy; } ;
struct timespec {int dummy; } ;
struct test_ctx {int ts_type; } ;
struct bintime {int dummy; } ;

/* Variables and functions */
#define  TT_BINTIME 133 
#define  TT_MONOTONIC 132 
#define  TT_REALTIME 131 
#define  TT_REALTIME_MICRO 130 
#define  TT_TIMESTAMP 129 
#define  TT_TS_BINTIME 128 
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static size_t
get_scm_size(struct test_ctx *tcp)
{
    switch (tcp->ts_type) {
    case TT_TIMESTAMP:
    case TT_REALTIME_MICRO:
        return (sizeof(struct timeval));

    case TT_BINTIME:
    case TT_TS_BINTIME:
        return (sizeof(struct bintime));

    case TT_REALTIME:
    case TT_MONOTONIC:
        return (sizeof(struct timespec));
    }
    abort();
}