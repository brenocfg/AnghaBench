#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  req; int /*<<< orphan*/  body; } ;
typedef  TYPE_1__ h2o_loopback_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  h2o_buffer_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_dispose_request (int /*<<< orphan*/ *) ; 

void h2o_loopback_destroy(h2o_loopback_conn_t *conn)
{
    h2o_buffer_dispose(&conn->body);
    h2o_dispose_request(&conn->req);
    free(conn);
}