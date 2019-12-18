#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  column; int /*<<< orphan*/  line; } ;
struct TYPE_21__ {int /*<<< orphan*/  column; int /*<<< orphan*/  line; } ;
struct TYPE_22__ {int error; int problem_value; char* problem; int problem_offset; char* context; TYPE_1__ problem_mark; TYPE_2__ context_mark; } ;
typedef  TYPE_3__ yaml_parser_t ;
typedef  TYPE_3__ yaml_emitter_t ;
typedef  TYPE_3__ yaml_document_t ;
typedef  int /*<<< orphan*/  parser ;
typedef  int /*<<< orphan*/  emitter ;
typedef  int /*<<< orphan*/  document ;

/* Variables and functions */
#define  YAML_COMPOSER_ERROR 134 
#define  YAML_EMITTER_ERROR 133 
#define  YAML_MEMORY_ERROR 132 
#define  YAML_PARSER_ERROR 131 
#define  YAML_READER_ERROR 130 
#define  YAML_SCANNER_ERROR 129 
#define  YAML_WRITER_ERROR 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  yaml_document_get_root_node (TYPE_3__*) ; 
 int /*<<< orphan*/  yaml_emitter_delete (TYPE_3__*) ; 
 int /*<<< orphan*/  yaml_emitter_dump (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  yaml_emitter_initialize (TYPE_3__*) ; 
 int /*<<< orphan*/  yaml_emitter_set_canonical (TYPE_3__*,int) ; 
 int /*<<< orphan*/  yaml_emitter_set_output_file (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yaml_emitter_set_unicode (TYPE_3__*,int) ; 
 int /*<<< orphan*/  yaml_parser_delete (TYPE_3__*) ; 
 int /*<<< orphan*/  yaml_parser_initialize (TYPE_3__*) ; 
 int /*<<< orphan*/  yaml_parser_load (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  yaml_parser_set_input_file (TYPE_3__*,int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
    int help = 0;
    int canonical = 0;
    int unicode = 0;
    int k;
    int done = 0;

    yaml_parser_t parser;
    yaml_emitter_t emitter;
    yaml_document_t document;

    /* Clear the objects. */

    memset(&parser, 0, sizeof(parser));
    memset(&emitter, 0, sizeof(emitter));
    memset(&document, 0, sizeof(document));

    /* Analyze command line options. */

    for (k = 1; k < argc; k ++)
    {
        if (strcmp(argv[k], "-h") == 0
                || strcmp(argv[k], "--help") == 0) {
            help = 1;
        }

        else if (strcmp(argv[k], "-c") == 0
                || strcmp(argv[k], "--canonical") == 0) {
            canonical = 1;
        }

        else if (strcmp(argv[k], "-u") == 0
                || strcmp(argv[k], "--unicode") == 0) {
            unicode = 1;
        }

        else {
            fprintf(stderr, "Unrecognized option: %s\n"
                    "Try `%s --help` for more information.\n",
                    argv[k], argv[0]);
            return 1;
        }
    }

    /* Display the help string. */

    if (help)
    {
        printf("%s [--canonical] [--unicode] <input >output\n"
                "or\n%s -h | --help\nReformat a YAML stream\n\nOptions:\n"
                "-h, --help\t\tdisplay this help and exit\n"
                "-c, --canonical\t\toutput in the canonical YAML format\n"
                "-u, --unicode\t\toutput unescaped non-ASCII characters\n",
                argv[0], argv[0]);
        return 0;
    }

    /* Initialize the parser and emitter objects. */

    if (!yaml_parser_initialize(&parser))
        goto parser_error;

    if (!yaml_emitter_initialize(&emitter))
        goto emitter_error;

    /* Set the parser parameters. */

    yaml_parser_set_input_file(&parser, stdin);

    /* Set the emitter parameters. */

    yaml_emitter_set_output_file(&emitter, stdout);

    yaml_emitter_set_canonical(&emitter, canonical);
    yaml_emitter_set_unicode(&emitter, unicode);

    /* The main loop. */

    while (!done)
    {
        /* Get the next event. */

        if (!yaml_parser_load(&parser, &document))
            goto parser_error;

        /* Check if this is the stream end. */

        if (!yaml_document_get_root_node(&document)) {
            done = 1;
        }

        /* Emit the event. */

        if (!yaml_emitter_dump(&emitter, &document))
            goto emitter_error;
    }

    yaml_parser_delete(&parser);
    yaml_emitter_delete(&emitter);

    return 0;

parser_error:

    /* Display a parser error message. */

    switch (parser.error)
    {
        case YAML_MEMORY_ERROR:
            fprintf(stderr, "Memory error: Not enough memory for parsing\n");
            break;

        case YAML_READER_ERROR:
            if (parser.problem_value != -1) {
                fprintf(stderr, "Reader error: %s: #%X at %d\n", parser.problem,
                        parser.problem_value, parser.problem_offset);
            }
            else {
                fprintf(stderr, "Reader error: %s at %d\n", parser.problem,
                        parser.problem_offset);
            }
            break;

        case YAML_SCANNER_ERROR:
            if (parser.context) {
                fprintf(stderr, "Scanner error: %s at line %d, column %d\n"
                        "%s at line %d, column %d\n", parser.context,
                        parser.context_mark.line+1, parser.context_mark.column+1,
                        parser.problem, parser.problem_mark.line+1,
                        parser.problem_mark.column+1);
            }
            else {
                fprintf(stderr, "Scanner error: %s at line %d, column %d\n",
                        parser.problem, parser.problem_mark.line+1,
                        parser.problem_mark.column+1);
            }
            break;

        case YAML_PARSER_ERROR:
            if (parser.context) {
                fprintf(stderr, "Parser error: %s at line %d, column %d\n"
                        "%s at line %d, column %d\n", parser.context,
                        parser.context_mark.line+1, parser.context_mark.column+1,
                        parser.problem, parser.problem_mark.line+1,
                        parser.problem_mark.column+1);
            }
            else {
                fprintf(stderr, "Parser error: %s at line %d, column %d\n",
                        parser.problem, parser.problem_mark.line+1,
                        parser.problem_mark.column+1);
            }
            break;

        case YAML_COMPOSER_ERROR:
            if (parser.context) {
                fprintf(stderr, "Composer error: %s at line %d, column %d\n"
                        "%s at line %d, column %d\n", parser.context,
                        parser.context_mark.line+1, parser.context_mark.column+1,
                        parser.problem, parser.problem_mark.line+1,
                        parser.problem_mark.column+1);
            }
            else {
                fprintf(stderr, "Composer error: %s at line %d, column %d\n",
                        parser.problem, parser.problem_mark.line+1,
                        parser.problem_mark.column+1);
            }
            break;

        default:
            /* Couldn't happen. */
            fprintf(stderr, "Internal error\n");
            break;
    }

    yaml_parser_delete(&parser);
    yaml_emitter_delete(&emitter);

    return 1;

emitter_error:

    /* Display an emitter error message. */

    switch (emitter.error)
    {
        case YAML_MEMORY_ERROR:
            fprintf(stderr, "Memory error: Not enough memory for emitting\n");
            break;

        case YAML_WRITER_ERROR:
            fprintf(stderr, "Writer error: %s\n", emitter.problem);
            break;

        case YAML_EMITTER_ERROR:
            fprintf(stderr, "Emitter error: %s\n", emitter.problem);
            break;

        default:
            /* Couldn't happen. */
            fprintf(stderr, "Internal error\n");
            break;
    }

    yaml_parser_delete(&parser);
    yaml_emitter_delete(&emitter);

    return 1;
}