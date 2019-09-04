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
struct TYPE_5__ {scalar_t__ start; scalar_t__ pointer; scalar_t__ last; scalar_t__ end; } ;
struct TYPE_6__ {int eof; TYPE_1__ raw_buffer; int /*<<< orphan*/  offset; int /*<<< orphan*/  read_handler_data; int /*<<< orphan*/  (* read_handler ) (int /*<<< orphan*/ ,scalar_t__,scalar_t__,size_t*) ;} ;
typedef  TYPE_2__ yaml_parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,size_t*) ; 
 int yaml_parser_set_reader_error (TYPE_2__*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
yaml_parser_update_raw_buffer(yaml_parser_t *parser)
{
    size_t size_read = 0;

    /* Return if the raw buffer is full. */

    if (parser->raw_buffer.start == parser->raw_buffer.pointer
            && parser->raw_buffer.last == parser->raw_buffer.end)
        return 1;

    /* Return on EOF. */

    if (parser->eof) return 1;

    /* Move the remaining bytes in the raw buffer to the beginning. */

    if (parser->raw_buffer.start < parser->raw_buffer.pointer
            && parser->raw_buffer.pointer < parser->raw_buffer.last) {
        memmove(parser->raw_buffer.start, parser->raw_buffer.pointer,
                parser->raw_buffer.last - parser->raw_buffer.pointer);
    }
    parser->raw_buffer.last -=
        parser->raw_buffer.pointer - parser->raw_buffer.start;
    parser->raw_buffer.pointer = parser->raw_buffer.start;

    /* Call the read handler to fill the buffer. */

    if (!parser->read_handler(parser->read_handler_data, parser->raw_buffer.last,
                parser->raw_buffer.end - parser->raw_buffer.last, &size_read)) {
        return yaml_parser_set_reader_error(parser, "input error",
                parser->offset, -1);
    }
    parser->raw_buffer.last += size_read;
    if (!size_read) {
        parser->eof = 1;
    }

    return 1;
}