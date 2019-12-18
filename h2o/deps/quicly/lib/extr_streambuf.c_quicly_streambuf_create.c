#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ingress; int /*<<< orphan*/  egress; } ;
typedef  TYPE_1__ quicly_streambuf_t ;
struct TYPE_6__ {TYPE_1__* data; } ;
typedef  TYPE_2__ quicly_stream_t ;

/* Variables and functions */
 int PTLS_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* malloc (size_t) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ptls_buffer_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_sendbuf_init (int /*<<< orphan*/ *) ; 

int quicly_streambuf_create(quicly_stream_t *stream, size_t sz)
{
    quicly_streambuf_t *sbuf;

    assert(sz >= sizeof(*sbuf));
    assert(stream->data == NULL);

    if ((sbuf = malloc(sz)) == NULL)
        return PTLS_ERROR_NO_MEMORY;
    quicly_sendbuf_init(&sbuf->egress);
    ptls_buffer_init(&sbuf->ingress, "", 0);
    if (sz != sizeof(*sbuf))
        memset((char *)sbuf + sizeof(*sbuf), 0, sz - sizeof(*sbuf));

    stream->data = sbuf;
    return 0;
}