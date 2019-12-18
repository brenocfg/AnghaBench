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
typedef  int /*<<< orphan*/  serf_request_t ;
typedef  int /*<<< orphan*/  serf_request_setup_t ;
typedef  int /*<<< orphan*/  serf_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/ * priority_request_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

serf_request_t *serf_connection_priority_request_create(
    serf_connection_t *conn,
    serf_request_setup_t setup,
    void *setup_baton)
{
    return priority_request_create(conn,
                                   0, /* not a ssltunnel CONNECT request */
                                   setup, setup_baton);
}