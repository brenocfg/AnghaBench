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
 int /*<<< orphan*/  TT_BINTIME ; 
 int /*<<< orphan*/  TT_MONOTONIC ; 
 int /*<<< orphan*/  TT_REALTIME ; 
 int /*<<< orphan*/  TT_REALTIME_MICRO ; 
 int /*<<< orphan*/  TT_TIMESTAMP ; 
 int /*<<< orphan*/  TT_TS_BINTIME ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  srandomdev () ; 
 int /*<<< orphan*/  test_run (int /*<<< orphan*/ ,int,int,char*) ; 

int
main(void)
{
    int i;

    srandomdev();

    for (i = 0; i < 2; i++) {
        test_run(0, i, 0, "send()/recv()");
        printf("OK\n");
        test_run(TT_TIMESTAMP, i, 1,
          "send()/recvmsg(), setsockopt(SO_TIMESTAMP, 1)");
        printf("OK\n");
        if (i == 0) {
            test_run(TT_BINTIME, i, 1,
              "send()/recvmsg(), setsockopt(SO_BINTIME, 1)");
            printf("OK\n");
        }
        test_run(TT_REALTIME_MICRO, i, 1,
          "send()/recvmsg(), setsockopt(SO_TS_CLOCK, SO_TS_REALTIME_MICRO)");
        printf("OK\n");
        test_run(TT_TS_BINTIME, i, 1,
          "send()/recvmsg(), setsockopt(SO_TS_CLOCK, SO_TS_BINTIME)");
        printf("OK\n");
        test_run(TT_REALTIME, i, 1,
          "send()/recvmsg(), setsockopt(SO_TS_CLOCK, SO_TS_REALTIME)");
        printf("OK\n");
        test_run(TT_MONOTONIC, i, 1,
          "send()/recvmsg(), setsockopt(SO_TS_CLOCK, SO_TS_MONOTONIC)");
        printf("OK\n");
    }
    exit(0);
}