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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct sockaddr {int dummy; } ;
struct sctphdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_SHUTDOWN_COMPLETE ; 
 int /*<<< orphan*/  sctp_send_resp_msg (struct sockaddr*,struct sockaddr*,struct sctphdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
sctp_send_shutdown_complete2(struct sockaddr *src, struct sockaddr *dst,
    struct sctphdr *sh,
    uint8_t mflowtype, uint32_t mflowid, uint16_t fibnum,
    uint32_t vrf_id, uint16_t port)
{
	sctp_send_resp_msg(src, dst, sh, 0, SCTP_SHUTDOWN_COMPLETE, NULL,
	    mflowtype, mflowid, fibnum,
	    vrf_id, port);
}