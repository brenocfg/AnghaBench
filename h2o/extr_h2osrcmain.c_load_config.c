#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {char* filename; scalar_t__ line; } ;
typedef  TYPE_2__ yoml_t ;
struct TYPE_16__ {char* filename; } ;
typedef  TYPE_3__ yoml_parse_args_t ;
struct TYPE_14__ {scalar_t__ line; } ;
struct TYPE_17__ {char* problem; TYPE_1__ problem_mark; } ;
typedef  TYPE_4__ yaml_parser_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yaml_parser_delete (TYPE_4__*) ; 
 int /*<<< orphan*/  yaml_parser_initialize (TYPE_4__*) ; 
 int /*<<< orphan*/  yaml_parser_set_input_file (TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* yoml_parse_document (TYPE_4__*,int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static yoml_t *load_config(yoml_parse_args_t *parse_args, yoml_t *source)
{
    FILE *fp;
    yaml_parser_t parser;
    yoml_t *yoml;

    if ((fp = fopen(parse_args->filename, "rb")) == NULL) {
        fprintf(stderr, "could not open configuration file %s: %s\n", parse_args->filename, strerror(errno));
        return NULL;
    }

    yaml_parser_initialize(&parser);
    yaml_parser_set_input_file(&parser, fp);

    yoml = yoml_parse_document(&parser, NULL, parse_args);

    if (yoml == NULL) {
        fprintf(stderr, "failed to parse configuration file %s line %d", parse_args->filename, (int)parser.problem_mark.line + 1);
        if (source != NULL) {
            fprintf(stderr, " (included from file %s line %d)", source->filename, (int)source->line + 1);
        }
        fprintf(stderr, ": %s\n", parser.problem);
    }

    yaml_parser_delete(&parser);

    fclose(fp);

    return yoml;
}