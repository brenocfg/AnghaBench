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
struct st_quicly_application_space_t {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * application; } ;
typedef  TYPE_1__ quicly_conn_t ;

/* Variables and functions */
 int PTLS_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  QUICLY_EPOCH_1RTT ; 
 scalar_t__ alloc_pn_space (int) ; 
 int create_handshake_flow (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_application_space(quicly_conn_t *conn)
{
    if ((conn->application = (void *)alloc_pn_space(sizeof(struct st_quicly_application_space_t))) == NULL)
        return PTLS_ERROR_NO_MEMORY;
    return create_handshake_flow(conn, QUICLY_EPOCH_1RTT);
}