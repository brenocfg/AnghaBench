#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  initial; } ;
typedef  TYPE_1__ quicly_conn_t ;

/* Variables and functions */
 unsigned int QUICLY_EPOCH_INITIAL ; 
 int /*<<< orphan*/  destroy_handshake_flow (TYPE_1__*,unsigned int) ; 
 int discard_sentmap_by_epoch (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  free_handshake_space (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int discard_initial_context(quicly_conn_t *conn)
{
    int ret;

    if ((ret = discard_sentmap_by_epoch(conn, 1u << QUICLY_EPOCH_INITIAL)) != 0)
        return ret;
    destroy_handshake_flow(conn, QUICLY_EPOCH_INITIAL);
    free_handshake_space(&conn->initial);

    return 0;
}