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
struct TYPE_5__ {int last; int pointer; } ;
struct TYPE_6__ {int offset; void* encoding; TYPE_1__ raw_buffer; int /*<<< orphan*/  eof; } ;
typedef  TYPE_2__ yaml_parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  BOM_UTF16BE ; 
 int /*<<< orphan*/  BOM_UTF16LE ; 
 int /*<<< orphan*/  BOM_UTF8 ; 
 void* YAML_UTF16BE_ENCODING ; 
 void* YAML_UTF16LE_ENCODING ; 
 void* YAML_UTF8_ENCODING ; 
 int /*<<< orphan*/  memcmp (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  yaml_parser_update_raw_buffer (TYPE_2__*) ; 

__attribute__((used)) static int
yaml_parser_determine_encoding(yaml_parser_t *parser)
{
    /* Ensure that we had enough bytes in the raw buffer. */

    while (!parser->eof 
            && parser->raw_buffer.last - parser->raw_buffer.pointer < 3) {
        if (!yaml_parser_update_raw_buffer(parser)) {
            return 0;
        }
    }

    /* Determine the encoding. */

    if (parser->raw_buffer.last - parser->raw_buffer.pointer >= 2
            && !memcmp(parser->raw_buffer.pointer, BOM_UTF16LE, 2)) {
        parser->encoding = YAML_UTF16LE_ENCODING;
        parser->raw_buffer.pointer += 2;
        parser->offset += 2;
    }
    else if (parser->raw_buffer.last - parser->raw_buffer.pointer >= 2
            && !memcmp(parser->raw_buffer.pointer, BOM_UTF16BE, 2)) {
        parser->encoding = YAML_UTF16BE_ENCODING;
        parser->raw_buffer.pointer += 2;
        parser->offset += 2;
    }
    else if (parser->raw_buffer.last - parser->raw_buffer.pointer >= 3
            && !memcmp(parser->raw_buffer.pointer, BOM_UTF8, 3)) {
        parser->encoding = YAML_UTF8_ENCODING;
        parser->raw_buffer.pointer += 3;
        parser->offset += 3;
    }
    else {
        parser->encoding = YAML_UTF8_ENCODING;
    }

    return 1;
}