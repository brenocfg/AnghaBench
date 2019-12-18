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
typedef  int /*<<< orphan*/  quicly_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUICLY_ERROR_RECEIVED_STATELESS_RESET ; 
 int /*<<< orphan*/  QUICLY_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATELESS_RESET_RECEIVE ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int handle_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe_now () ; 
 int /*<<< orphan*/  ptls_iovec_init (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_stateless_reset(quicly_conn_t *conn)
{
    QUICLY_PROBE(STATELESS_RESET_RECEIVE, conn, probe_now());
    return handle_close(conn, QUICLY_ERROR_RECEIVED_STATELESS_RESET, UINT64_MAX, ptls_iovec_init("", 0));
}