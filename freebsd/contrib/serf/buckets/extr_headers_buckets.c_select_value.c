#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int state; int amt_read; TYPE_1__* cur_read; TYPE_1__* list; } ;
typedef  TYPE_2__ headers_context_t ;
typedef  int apr_size_t ;
struct TYPE_4__ {char* header; int header_size; char* value; int value_size; } ;

/* Variables and functions */
#define  READ_CRLF 133 
#define  READ_DONE 132 
#define  READ_HEADER 131 
#define  READ_SEP 130 
 int READ_START ; 
#define  READ_TERM 129 
#define  READ_VALUE 128 

__attribute__((used)) static void select_value(
    headers_context_t *ctx,
    const char **value,
    apr_size_t *len)
{
    const char *v;
    apr_size_t l;

    if (ctx->state == READ_START) {
        if (ctx->list == NULL) {
            /* No headers. Move straight to the TERM state. */
            ctx->state = READ_TERM;
        }
        else {
            ctx->state = READ_HEADER;
            ctx->cur_read = ctx->list;
        }
        ctx->amt_read = 0;
    }

    switch (ctx->state) {
    case READ_HEADER:
        v = ctx->cur_read->header;
        l = ctx->cur_read->header_size;
        break;
    case READ_SEP:
        v = ": ";
        l = 2;
        break;
    case READ_VALUE:
        v = ctx->cur_read->value;
        l = ctx->cur_read->value_size;
        break;
    case READ_CRLF:
    case READ_TERM:
        v = "\r\n";
        l = 2;
        break;
    case READ_DONE:
        *len = 0;
        return;
    default:
        /* Not reachable */
        return;
    }

    *value = v + ctx->amt_read;
    *len = l - ctx->amt_read;
}