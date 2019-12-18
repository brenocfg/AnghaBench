#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int length; unsigned char command; char const* key; scalar_t__ status; int flags; char const* data; size_t data_len; void* value; void* cas_unique; int /*<<< orphan*/  serial; scalar_t__ key_len; } ;
typedef  TYPE_1__ yrmcds_response ;
typedef  scalar_t__ yrmcds_error ;
struct TYPE_9__ {int invalid; scalar_t__ last_size; size_t used; char* recvbuf; char* decompressed; scalar_t__ compress_size; scalar_t__ text_mode; } ;
typedef  TYPE_2__ yrmcds ;
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ BINARY_HEADER_SIZE ; 
 scalar_t__ INT_MAX ; 
 int LZ4_decompress_safe (char const*,char*,int,int) ; 
 scalar_t__ MAX_CAPACITY ; 
 scalar_t__ UINT32_MAX ; 
 scalar_t__ YRMCDS_BAD_ARGUMENT ; 
 unsigned char YRMCDS_CMD_DECREMENT ; 
 unsigned char YRMCDS_CMD_INCREMENT ; 
 int YRMCDS_FLAG_COMPRESS ; 
 scalar_t__ YRMCDS_OK ; 
 scalar_t__ YRMCDS_OUT_OF_MEMORY ; 
 scalar_t__ YRMCDS_PROTOCOL_ERROR ; 
 scalar_t__ YRMCDS_STATUS_OK ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 void* ntoh16 (char const*) ; 
 void* ntoh32 (char const*) ; 
 void* ntoh64 (char const*) ; 
 scalar_t__ recv_data (TYPE_2__*) ; 
 scalar_t__ text_recv (TYPE_2__*,TYPE_1__*) ; 

yrmcds_error yrmcds_recv(yrmcds* c, yrmcds_response* r) {
    if( c == NULL || r == NULL )
        return YRMCDS_BAD_ARGUMENT;
    if( c->invalid )
        return YRMCDS_PROTOCOL_ERROR;

    if( c->last_size > 0 ) {
        size_t remain = c->used - c->last_size;
        if( remain > 0 )
            memmove(c->recvbuf, c->recvbuf + c->last_size, remain);
        c->used = remain;
        c->last_size = 0;
        free(c->decompressed);
        c->decompressed = NULL;
    }

    if( c->text_mode ) {
        return text_recv(c, r);
    }

    while( c->used < BINARY_HEADER_SIZE ) {
        yrmcds_error e = recv_data(c);
        if( e != 0 ) return e;
    }

    if( *c->recvbuf != '\x81' ) {
        c->invalid = 1;
        return YRMCDS_PROTOCOL_ERROR;
    }
    uint32_t total_len = ntoh32(c->recvbuf + 8);
    if( total_len > MAX_CAPACITY ) {
        c->invalid = 1;
        return YRMCDS_PROTOCOL_ERROR;
    }
    while( c->used < (BINARY_HEADER_SIZE + total_len) ) {
        yrmcds_error e = recv_data(c);
        if( e != 0 ) return e;
    }

    uint16_t key_len = ntoh16(c->recvbuf + 2);
    uint8_t extras_len = *(unsigned char*)(c->recvbuf + 4);
    if( total_len < (key_len + extras_len) ) {
        c->invalid = 1;
        return YRMCDS_PROTOCOL_ERROR;
    }

    const char* pkey = c->recvbuf + (BINARY_HEADER_SIZE + extras_len);
    r->length = BINARY_HEADER_SIZE + total_len;
    r->command = *(unsigned char*)(c->recvbuf + 1);
    r->key = key_len ? pkey : NULL;
    r->key_len = key_len;
    r->status = ntoh16(c->recvbuf + 6);
    memcpy(&(r->serial), c->recvbuf + 12, 4);
    r->cas_unique = ntoh64(c->recvbuf + 16);
    r->flags = 0;
    if( extras_len > 0 ) {
        if( extras_len != 4 ) {
            c->invalid = 1;
            return YRMCDS_PROTOCOL_ERROR;
        }
        r->flags = ntoh32(c->recvbuf + BINARY_HEADER_SIZE);
    }

    size_t data_len = total_len - key_len - extras_len;
    const char* pdata = pkey + key_len;

    if( (r->command == YRMCDS_CMD_INCREMENT ||
         r->command == YRMCDS_CMD_DECREMENT) &&
        (r->status == YRMCDS_STATUS_OK) ) {
        r->data = NULL;
        r->data_len = 0;
        if( data_len != 8 ) {
            c->invalid = 1;
            return YRMCDS_PROTOCOL_ERROR;
        }
        r->value = ntoh64(pdata);
        c->last_size = r->length;
        return YRMCDS_OK;
    }
    r->value = 0;
    r->data = data_len ? pdata : NULL;
    r->data_len = data_len;

#ifdef LIBYRMCDS_USE_LZ4
    if( c->compress_size && (r->flags & YRMCDS_FLAG_COMPRESS) ) {
        if( data_len == 0 ) {
            c->invalid = 1;
            return YRMCDS_PROTOCOL_ERROR;
        }
        r->flags &= ~(uint32_t)YRMCDS_FLAG_COMPRESS;
        uint32_t decompress_size = ntoh32(pdata);
        if( UINT32_MAX > INT_MAX ) {
            if( decompress_size > INT_MAX ) {
                c->invalid = 1;
                return YRMCDS_PROTOCOL_ERROR;
            }
        }
        c->decompressed = (char*)malloc(decompress_size);
        if( c->decompressed == NULL )
            return YRMCDS_OUT_OF_MEMORY;
        int d = LZ4_decompress_safe(pdata + sizeof(uint32_t),
                                    c->decompressed,
                                    (int)(data_len - sizeof(uint32_t)),
                                    (int)decompress_size);
        if( d != decompress_size ) {
            c->invalid = 1;
            return YRMCDS_PROTOCOL_ERROR;
        }
        r->data = c->decompressed;
        r->data_len = decompress_size;
    }
#endif // LIBYRMCDS_USE_LZ4

    c->last_size = r->length;
    return YRMCDS_OK;
}