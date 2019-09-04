#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned char* pointer; } ;
struct TYPE_8__ {int unread; char* problem; int problem_offset; int eof; TYPE_1__ buffer; } ;
typedef  TYPE_2__ yaml_parser_t ;

/* Variables and functions */
 int LONG ; 
 int /*<<< orphan*/  assert (unsigned char*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  yaml_parser_delete (TYPE_2__*) ; 
 int /*<<< orphan*/  yaml_parser_initialize (TYPE_2__*) ; 
 int /*<<< orphan*/  yaml_parser_set_input_string (TYPE_2__*,unsigned char*,int) ; 
 int /*<<< orphan*/  yaml_parser_update_buffer (TYPE_2__*,int) ; 

int check_long_utf16(void)
{
    yaml_parser_t parser;
    int k = 0;
    int j;
    int failed = 0;
    unsigned char ch0, ch1;
    unsigned char *buffer = malloc(2+LONG*2);
    assert(buffer);
    printf("checking a long utf16 sequence...\n");
    buffer[k++] = '\xff';
    buffer[k++] = '\xfe';
    for (j = 0; j < LONG; j ++) {
        if (j % 2) {
            buffer[k++] = '\x10';
            buffer[k++] = '\x04';
        }
        else {
            buffer[k++] = '/';
            buffer[k++] = '\x04';
        }
    }
    yaml_parser_initialize(&parser);
    yaml_parser_set_input_string(&parser, buffer, 2+LONG*2);
    for (k = 0; k < LONG; k++) {
        if (!parser.unread) {
            if (!yaml_parser_update_buffer(&parser, 1)) {
                printf("\treader error: %s at %d\n", parser.problem, parser.problem_offset);
                failed = 1;
                break;
            }
        }
        if (!parser.unread) {
            printf("\tnot enough characters at %d\n", k);
            failed = 1;
            break;
        }
        if (k % 2) {
            ch0 = '\xd0';
            ch1 = '\x90';
        }
        else {
            ch0 = '\xd0';
            ch1 = '\xaf';
        }
        if (parser.buffer.pointer[0] != ch0 || parser.buffer.pointer[1] != ch1) {
            printf("\tincorrect UTF-8 sequence: %X %X instead of %X %X\n",
                    (int)parser.buffer.pointer[0], (int)parser.buffer.pointer[1],
                    (int)ch0, (int)ch1);
            failed = 1;
            break;
        }
        parser.buffer.pointer += 2;
        parser.unread -= 1;
    }
    if (!failed) {
        if (!yaml_parser_update_buffer(&parser, 1)) {
            printf("\treader error: %s at %d\n", parser.problem, parser.problem_offset);
            failed = 1;
        }
        else if (parser.buffer.pointer[0] != '\0') {
            printf("\texpected NUL, found %X (eof=%d, unread=%d)\n", (int)parser.buffer.pointer[0], parser.eof, parser.unread);
            failed = 1;
        }
    }
    yaml_parser_delete(&parser);
    free(buffer);
    printf("checking a long utf16 sequence: %d fail(s)\n", failed);
    return failed;
}