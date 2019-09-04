#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ yrmcds_error ;
typedef  scalar_t__ yrmcds_cnt_status ;
struct TYPE_10__ {int command; scalar_t__ status; scalar_t__ body_length; int /*<<< orphan*/ * stats; scalar_t__* body; void* resources; void* current_consumption; scalar_t__ name_length; scalar_t__ max_consumption; int /*<<< orphan*/  serial; } ;
typedef  TYPE_1__ yrmcds_cnt_response ;
typedef  int yrmcds_cnt_command ;
struct TYPE_11__ {int invalid; scalar_t__ last_size; size_t used; int /*<<< orphan*/  stats; scalar_t__* recvbuf; } ;
typedef  TYPE_2__ yrmcds_cnt ;
typedef  int uint8_t ;

/* Variables and functions */
 scalar_t__ HEADER_SIZE ; 
 scalar_t__ YRMCDS_BAD_ARGUMENT ; 
#define  YRMCDS_CNT_CMD_ACQUIRE 131 
#define  YRMCDS_CNT_CMD_DUMP 130 
#define  YRMCDS_CNT_CMD_GET 129 
#define  YRMCDS_CNT_CMD_STATS 128 
 scalar_t__ YRMCDS_OK ; 
 scalar_t__ YRMCDS_PROTOCOL_ERROR ; 
 scalar_t__ YRMCDS_STATUS_OK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,size_t) ; 
 void* ntoh32 (scalar_t__*) ; 
 scalar_t__ parse_dump_record (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ parse_statistics (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ recv_data (TYPE_2__*) ; 

yrmcds_error
yrmcds_cnt_recv(yrmcds_cnt* c, yrmcds_cnt_response* r) {
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
    }

    while( c->used < HEADER_SIZE ) {
        yrmcds_error e = recv_data(c);
        if( e != YRMCDS_OK ) return e;
    }

    if( (uint8_t)c->recvbuf[0] != 0x91 ) {
        c->invalid = 1;
        return YRMCDS_PROTOCOL_ERROR;
    }

    r->command = (yrmcds_cnt_command)c->recvbuf[1];
    r->status = (yrmcds_cnt_status)c->recvbuf[2];
    r->body_length = ntoh32(c->recvbuf + 4);
    memcpy(&r->serial, c->recvbuf + 8, sizeof(r->serial));
    r->body = NULL;
    r->resources = 0;
    r->current_consumption = 0;
    r->max_consumption = 0;
    r->name_length = 0;
    r->stats = NULL;

    if( r->body_length > 0 ) {
        while( c->used < HEADER_SIZE + r->body_length ) {
            yrmcds_error e = recv_data(c);
            if( e != YRMCDS_OK ) return e;
        }
        r->body = c->recvbuf + HEADER_SIZE;
    }
    c->last_size = HEADER_SIZE + r->body_length;

    if( r->status != YRMCDS_STATUS_OK )
        return YRMCDS_OK;

    yrmcds_error err;
    switch( r->command ) {
    case YRMCDS_CNT_CMD_GET:
        if( r->body_length < 4 ) {
            c->invalid = 1;
            return YRMCDS_PROTOCOL_ERROR;
        }
        r->current_consumption = ntoh32(r->body);
        break;

    case YRMCDS_CNT_CMD_ACQUIRE:
        if( r->body_length < 4 ) {
            c->invalid = 1;
            return YRMCDS_PROTOCOL_ERROR;
        }
        r->resources = ntoh32(r->body);
        break;

    case YRMCDS_CNT_CMD_STATS:
        err = parse_statistics(c, r);
        if( err != YRMCDS_OK ) {
            c->invalid = 1;
            return err;
        }
        r->stats = &c->stats;
        break;

    case YRMCDS_CNT_CMD_DUMP:
        err = parse_dump_record(c, r);
        if( err != YRMCDS_OK ) {
            c->invalid = 1;
            return err;
        }
        break;

    default:
        // No body
        break;
    }
    return YRMCDS_OK;
}