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
struct st_h2o_http1client_t {char* _chunk_len_str; } ;
struct TYPE_5__ {int len; char* base; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 TYPE_1__ h2o_iovec_init (char*,int) ; 
 int snprintf (char*,int,char*,int) ; 

size_t encode_chunk(struct st_h2o_http1client_t *client, h2o_iovec_t *bufs, h2o_iovec_t chunk, size_t *bytes)
{
    *bytes = 0;

    size_t i = 0;
    bufs[i].len = snprintf(client->_chunk_len_str, sizeof(client->_chunk_len_str), "%zx\r\n", chunk.len);
    *bytes += bufs[i].len;
    bufs[i++].base = client->_chunk_len_str;

    if (chunk.base != NULL) {
        bufs[i++] = h2o_iovec_init(chunk.base, chunk.len);
        *bytes += chunk.len;
    }
    bufs[i++] = h2o_iovec_init("\r\n", 2);
    *bytes += 2;

    return i;
}