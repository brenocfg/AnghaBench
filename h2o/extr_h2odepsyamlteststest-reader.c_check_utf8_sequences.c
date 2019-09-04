#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ error; int problem_value; char* problem; int problem_offset; } ;
typedef  TYPE_1__ yaml_parser_t ;
struct TYPE_8__ {char* test; char* title; int result; } ;

/* Variables and functions */
 scalar_t__ YAML_READER_ERROR ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_6__* utf8_sequences ; 
 int /*<<< orphan*/  yaml_parser_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  yaml_parser_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  yaml_parser_set_input_string (TYPE_1__*,unsigned char*,int) ; 
 int yaml_parser_update_buffer (TYPE_1__*,int) ; 

int check_utf8_sequences(void)
{
    yaml_parser_t parser;
    int failed = 0;
    int k;
    printf("checking utf-8 sequences...\n");
    for (k = 0; utf8_sequences[k].test; k++) {
        char *title = utf8_sequences[k].title;
        int check = utf8_sequences[k].result;
        int result;
        char *start = utf8_sequences[k].test;
        char *end = start;
        printf("\t%s:\n", title);
        while(1) {
            while (*end != '|' && *end != '!') end++;
            yaml_parser_initialize(&parser);
            yaml_parser_set_input_string(&parser, (unsigned char *)start, end-start);
            result = yaml_parser_update_buffer(&parser, end-start);
            if (result != check) {
                printf("\t\t- ");
                failed ++;
            }
            else {
                printf("\t\t+ ");
            }
            if (!parser.error) {
                printf("(no error)\n");
            }
            else if (parser.error == YAML_READER_ERROR) {
                if (parser.problem_value != -1) {
                    printf("(reader error: %s: #%X at %d)\n",
                            parser.problem, parser.problem_value, parser.problem_offset);
                }
                else {
                    printf("(reader error: %s at %d)\n",
                            parser.problem, parser.problem_offset);
                }
            }
            if (*end == '!') break;
            start = ++end;
            yaml_parser_delete(&parser);
        };
        printf("\n");
    }
    printf("checking utf-8 sequences: %d fail(s)\n", failed);
    return failed;
}