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
typedef  int /*<<< orphan*/  quicly_streambuf_t ;
struct TYPE_5__ {int /*<<< orphan*/ * callbacks; } ;
typedef  TYPE_1__ quicly_stream_t ;
typedef  int /*<<< orphan*/  quicly_stream_id_t ;
typedef  int /*<<< orphan*/  quicly_conn_t ;

/* Variables and functions */
 int PTLS_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  crypto_stream_callbacks ; 
 int /*<<< orphan*/  destroy_stream (TYPE_1__*,int) ; 
 TYPE_1__* open_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int quicly_streambuf_create (TYPE_1__*,int) ; 

__attribute__((used)) static int create_handshake_flow(quicly_conn_t *conn, size_t epoch)
{
    quicly_stream_t *stream;
    int ret;

    if ((stream = open_stream(conn, -(quicly_stream_id_t)(1 + epoch), 65536, 65536)) == NULL)
        return PTLS_ERROR_NO_MEMORY;
    if ((ret = quicly_streambuf_create(stream, sizeof(quicly_streambuf_t))) != 0) {
        destroy_stream(stream, ret);
        return ret;
    }
    stream->callbacks = &crypto_stream_callbacks;

    return 0;
}