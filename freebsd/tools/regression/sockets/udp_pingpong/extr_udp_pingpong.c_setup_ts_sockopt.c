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
typedef  int /*<<< orphan*/  sval2 ;
typedef  int /*<<< orphan*/  sval1 ;
struct test_ctx {int ts_type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int SO_BINTIME ; 
 int SO_TIMESTAMP ; 
 int SO_TS_CLOCK ; 
#define  TT_BINTIME 133 
#define  TT_MONOTONIC 132 
#define  TT_REALTIME 131 
#define  TT_REALTIME_MICRO 130 
#define  TT_TIMESTAMP 129 
#define  TT_TS_BINTIME 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ,int,int,...) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static void
setup_ts_sockopt(struct test_ctx *tcp, int fd)
{
    int rval, oname1, oname2, sval1, sval2;

    oname1 = SO_TIMESTAMP;
    oname2 = -1;
    sval2 = -1;

    switch (tcp->ts_type) {
    case TT_REALTIME_MICRO:
    case TT_TS_BINTIME:
    case TT_REALTIME:
    case TT_MONOTONIC:
        oname2 = SO_TS_CLOCK;
        sval2 = tcp->ts_type;
        break;

    case TT_TIMESTAMP:
        break;

    case TT_BINTIME:
        oname1 = SO_BINTIME;
        break;

    default:
        abort();
    }

    sval1 = 1;
    rval = setsockopt(fd, SOL_SOCKET, oname1, &sval1,
      sizeof(sval1));
    if (rval != 0) {
        err(1, "%s: setup_udp: setsockopt(%d, %d, 1)", tcp->name,
          fd, oname1);
    }
    if (oname2 == -1)
        return;
    rval = setsockopt(fd, SOL_SOCKET, oname2, &sval2,
      sizeof(sval2));
    if (rval != 0) {
        err(1, "%s: setup_udp: setsockopt(%d, %d, %d)",
          tcp->name, fd, oname2, sval2);
    }
}