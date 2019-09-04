#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* start; } ;
struct TYPE_9__ {char* problem; int problem_offset; int unread; TYPE_1__ buffer; } ;
typedef  TYPE_2__ yaml_parser_t ;
struct TYPE_10__ {char* test; char* title; int result; } ;

/* Variables and functions */
 char* bom_original ; 
 TYPE_7__* boms ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  yaml_parser_delete (TYPE_2__*) ; 
 int /*<<< orphan*/  yaml_parser_initialize (TYPE_2__*) ; 
 int /*<<< orphan*/  yaml_parser_set_input_string (TYPE_2__*,unsigned char*,int) ; 
 int yaml_parser_update_buffer (TYPE_2__*,int) ; 

int check_boms(void)
{
    yaml_parser_t parser;
    int failed = 0;
    int k;
    printf("checking boms...\n");
    for (k = 0; boms[k].test; k++) {
        char *title = boms[k].title;
        int check = boms[k].result;
        int result;
        char *start = boms[k].test;
        char *end = start;
        while (*end != '!') end++;
        printf("\t%s: ", title);
        yaml_parser_initialize(&parser);
        yaml_parser_set_input_string(&parser, (unsigned char *)start, end-start);
        result = yaml_parser_update_buffer(&parser, end-start);
        if (!result) {
            printf("- (reader error: %s at %d)\n", parser.problem, parser.problem_offset);
            failed++;
        }
        else {
            if (parser.unread != check) {
                printf("- (length=%d while expected length=%d)\n", parser.unread, check);
                failed++;
            }
            else if (memcmp(parser.buffer.start, bom_original, check) != 0) {
                printf("- (value '%s' does not equal to the original value '%s')\n", parser.buffer.start, bom_original);
                failed++;
            }
            else {
                printf("+\n");
            }
        }
        yaml_parser_delete(&parser);
    }
    printf("checking boms: %d fail(s)\n", failed);
    return failed;
}