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
typedef  scalar_t__ h2o_send_state_t ;
struct TYPE_5__ {char* base; int len; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 scalar_t__ H2O_SEND_STATE_ERROR ; 
 scalar_t__ H2O_SEND_STATE_FINAL ; 
 TYPE_1__ h2o_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,size_t) ; 

__attribute__((used)) static void encode_chunked(h2o_iovec_t *prefix, h2o_iovec_t *suffix, h2o_send_state_t state, size_t chunk_size, int send_trailers,
                           char *buffer)
{
    *prefix = h2o_iovec_init(NULL, 0);
    *suffix = h2o_iovec_init(NULL, 0);

    /* create chunk header and output data */
    if (chunk_size != 0) {
        prefix->base = buffer;
        prefix->len = sprintf(buffer, "%zx\r\n", chunk_size);
        if (state != H2O_SEND_STATE_ERROR) {
            suffix->base = "\r\n0\r\n\r\n";
            suffix->len = state == H2O_SEND_STATE_FINAL ? (send_trailers ? 5 : 7) : 2;
        }
    } else if (state == H2O_SEND_STATE_FINAL) {
        suffix->base = "0\r\n\r\n";
        suffix->len = send_trailers ? 3 : 5;
    }

    /* if state is error, send a broken chunk to pass the error down to the browser */
    if (state == H2O_SEND_STATE_ERROR) {
        suffix->base = "\r\n1\r\n";
        suffix->len = 5;
    }
}