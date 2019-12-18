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
typedef  int /*<<< orphan*/  quicly_stream_t ;
typedef  int /*<<< orphan*/  quicly_stream_id_t ;
typedef  int /*<<< orphan*/  quicly_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * quicly_get_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_handshake_flow(quicly_conn_t *conn, size_t epoch)
{
    quicly_stream_t *stream = quicly_get_stream(conn, -(quicly_stream_id_t)(1 + epoch));
    if (stream != NULL)
        destroy_stream(stream, 0);
}