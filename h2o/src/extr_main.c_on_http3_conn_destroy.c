#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_http3_conn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy_connection ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__ H2O_HTTP3_CONN_CALLBACKS ; 
 int /*<<< orphan*/  num_quic_connections (int) ; 
 int /*<<< orphan*/  on_connection_close () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_http3_conn_destroy(h2o_http3_conn_t *conn)
{
    on_connection_close();
    num_quic_connections(-1);

    H2O_HTTP3_CONN_CALLBACKS.destroy_connection(conn);
}