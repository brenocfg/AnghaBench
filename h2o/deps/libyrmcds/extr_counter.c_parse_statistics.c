#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ yrmcds_error ;
struct TYPE_7__ {scalar_t__ count; } ;
typedef  TYPE_1__ yrmcds_cnt_statistics ;
struct TYPE_8__ {char* body; int body_length; } ;
typedef  TYPE_2__ yrmcds_cnt_response ;
struct TYPE_9__ {TYPE_1__ stats; } ;
typedef  TYPE_3__ yrmcds_cnt ;
typedef  int uint16_t ;

/* Variables and functions */
 scalar_t__ YRMCDS_OK ; 
 scalar_t__ YRMCDS_PROTOCOL_ERROR ; 
 scalar_t__ append_stat (TYPE_1__*,int,int,char const*,char const*) ; 
 int ntoh16 (char const*) ; 

__attribute__((used)) static yrmcds_error
parse_statistics(yrmcds_cnt* c, const yrmcds_cnt_response* r) {
    yrmcds_cnt_statistics* s = &c->stats;
    s->count = 0;

    const char* p = r->body;
    const char* end = r->body + r->body_length;
    while( p < end ) {
        if( p + 4 > end )
            return YRMCDS_PROTOCOL_ERROR;
        uint16_t name_len = ntoh16(p);
        uint16_t value_len = ntoh16(p + 2);
        if( p + 4 + name_len + value_len > end )
            return YRMCDS_PROTOCOL_ERROR;
        yrmcds_error err =
            append_stat(s, name_len, value_len, p + 4, p + 4 + name_len);
        if( err != YRMCDS_OK )
            return err;
        p += 4 + name_len + value_len;
    }
    return YRMCDS_OK;
}