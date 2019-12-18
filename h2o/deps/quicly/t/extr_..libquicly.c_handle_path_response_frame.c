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
struct st_quicly_handle_payload_state_t {int dummy; } ;
typedef  int /*<<< orphan*/  quicly_conn_t ;

/* Variables and functions */
 int QUICLY_TRANSPORT_ERROR_PROTOCOL_VIOLATION ; 

__attribute__((used)) static int handle_path_response_frame(quicly_conn_t *conn, struct st_quicly_handle_payload_state_t *state)
{
    return QUICLY_TRANSPORT_ERROR_PROTOCOL_VIOLATION;
}