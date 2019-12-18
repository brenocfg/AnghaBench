#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  version; } ;
struct TYPE_7__ {TYPE_1__ super; } ;
typedef  TYPE_2__ quicly_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUICLY_PROBE (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERSION_SWITCH ; 
 int discard_sentmap_by_epoch (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  probe_now () ; 

__attribute__((used)) static int negotiate_using_version(quicly_conn_t *conn, uint32_t version)
{
    /* set selected version */
    conn->super.version = version;
    QUICLY_PROBE(VERSION_SWITCH, conn, probe_now(), version);

    /* reschedule all the packets that have been sent for immediate resend */
    return discard_sentmap_by_epoch(conn, ~0u);
}