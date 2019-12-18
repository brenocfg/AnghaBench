#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ostream_tail; int /*<<< orphan*/ * ostream_head; } ;
typedef  TYPE_1__ serf_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  serf_bucket_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_ostream(serf_connection_t *conn)
{
    if (conn->ostream_head != NULL) {
        serf_bucket_destroy(conn->ostream_head);
        conn->ostream_head = NULL;
        conn->ostream_tail = NULL;
    }
}