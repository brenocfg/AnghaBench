#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_54__   TYPE_9__ ;
typedef  struct TYPE_53__   TYPE_8__ ;
typedef  struct TYPE_52__   TYPE_7__ ;
typedef  struct TYPE_51__   TYPE_6__ ;
typedef  struct TYPE_50__   TYPE_5__ ;
typedef  struct TYPE_49__   TYPE_4__ ;
typedef  struct TYPE_48__   TYPE_3__ ;
typedef  struct TYPE_47__   TYPE_2__ ;
typedef  struct TYPE_46__   TYPE_1__ ;
typedef  struct TYPE_45__   TYPE_14__ ;
typedef  struct TYPE_44__   TYPE_13__ ;
typedef  struct TYPE_43__   TYPE_12__ ;
typedef  struct TYPE_42__   TYPE_11__ ;
typedef  struct TYPE_41__   TYPE_10__ ;

/* Type definitions */
struct TYPE_43__ {int major; int minor; } ;
typedef  TYPE_12__ yaml_version_directive_t ;
struct TYPE_44__ {char* handle; char* prefix; } ;
typedef  TYPE_13__ yaml_tag_directive_t ;
typedef  int /*<<< orphan*/  yaml_sequence_style_t ;
typedef  int /*<<< orphan*/  yaml_scalar_style_t ;
struct TYPE_42__ {int /*<<< orphan*/  column; int /*<<< orphan*/  line; } ;
struct TYPE_41__ {int /*<<< orphan*/  column; int /*<<< orphan*/  line; } ;
struct TYPE_53__ {char* anchor; char* tag; int /*<<< orphan*/  style; int /*<<< orphan*/  implicit; } ;
struct TYPE_52__ {char* anchor; char* tag; int /*<<< orphan*/  style; int /*<<< orphan*/  implicit; } ;
struct TYPE_51__ {char* anchor; char* tag; char* value; int length; int /*<<< orphan*/  style; int /*<<< orphan*/  quoted_implicit; int /*<<< orphan*/  plain_implicit; } ;
struct TYPE_50__ {char* anchor; } ;
struct TYPE_49__ {int /*<<< orphan*/  implicit; } ;
struct TYPE_47__ {TYPE_13__* end; TYPE_13__* start; } ;
struct TYPE_48__ {int /*<<< orphan*/  implicit; TYPE_2__ tag_directives; TYPE_12__* version_directive; } ;
struct TYPE_46__ {int /*<<< orphan*/  encoding; } ;
struct TYPE_54__ {TYPE_8__ mapping_start; TYPE_7__ sequence_start; TYPE_6__ scalar; TYPE_5__ alias; TYPE_4__ document_end; TYPE_3__ document_start; TYPE_1__ stream_start; } ;
struct TYPE_45__ {int type; int error; int problem_value; char* problem; int problem_offset; char* context; TYPE_11__ problem_mark; TYPE_10__ context_mark; TYPE_9__ data; } ;
typedef  TYPE_14__ yaml_parser_t ;
typedef  TYPE_14__ yaml_event_t ;
typedef  int /*<<< orphan*/  yaml_encoding_t ;
typedef  TYPE_14__ yaml_emitter_t ;
typedef  TYPE_14__ yaml_document_t ;
typedef  int /*<<< orphan*/  parser ;
typedef  int /*<<< orphan*/  output_document ;
typedef  int /*<<< orphan*/  input_event ;
typedef  int /*<<< orphan*/  emitter ;

/* Variables and functions */
#define  YAML_ALIAS_EVENT 143 
 int /*<<< orphan*/  YAML_BLOCK_MAPPING_STYLE ; 
 int /*<<< orphan*/  YAML_BLOCK_SEQUENCE_STYLE ; 
 int /*<<< orphan*/ * YAML_BOOL_TAG ; 
#define  YAML_DOCUMENT_END_EVENT 142 
#define  YAML_DOCUMENT_START_EVENT 141 
 int /*<<< orphan*/  YAML_DOUBLE_QUOTED_SCALAR_STYLE ; 
#define  YAML_EMITTER_ERROR 140 
 int /*<<< orphan*/  YAML_FLOW_MAPPING_STYLE ; 
 int /*<<< orphan*/  YAML_FLOW_SEQUENCE_STYLE ; 
 int /*<<< orphan*/  YAML_FOLDED_SCALAR_STYLE ; 
 int /*<<< orphan*/ * YAML_INT_TAG ; 
 int /*<<< orphan*/  YAML_LITERAL_SCALAR_STYLE ; 
#define  YAML_MAPPING_END_EVENT 139 
#define  YAML_MAPPING_START_EVENT 138 
#define  YAML_MEMORY_ERROR 137 
#define  YAML_PARSER_ERROR 136 
 int /*<<< orphan*/  YAML_PLAIN_SCALAR_STYLE ; 
#define  YAML_READER_ERROR 135 
#define  YAML_SCALAR_EVENT 134 
#define  YAML_SCANNER_ERROR 133 
#define  YAML_SEQUENCE_END_EVENT 132 
#define  YAML_SEQUENCE_START_EVENT 131 
 int /*<<< orphan*/  YAML_SINGLE_QUOTED_SCALAR_STYLE ; 
#define  YAML_STREAM_END_EVENT 130 
#define  YAML_STREAM_START_EVENT 129 
 int /*<<< orphan*/  YAML_UTF16BE_ENCODING ; 
 int /*<<< orphan*/  YAML_UTF16LE_ENCODING ; 
 int /*<<< orphan*/  YAML_UTF8_ENCODING ; 
#define  YAML_WRITER_ERROR 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_14__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int yaml_document_add_mapping (TYPE_14__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int yaml_document_add_scalar (TYPE_14__*,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int yaml_document_add_sequence (TYPE_14__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yaml_document_append_mapping_pair (TYPE_14__*,int,int,int) ; 
 int /*<<< orphan*/  yaml_document_append_sequence_item (TYPE_14__*,int,int) ; 
 int /*<<< orphan*/  yaml_document_delete (TYPE_14__*) ; 
 int /*<<< orphan*/  yaml_document_initialize (TYPE_14__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yaml_emitter_close (TYPE_14__*) ; 
 int /*<<< orphan*/  yaml_emitter_delete (TYPE_14__*) ; 
 int /*<<< orphan*/  yaml_emitter_dump (TYPE_14__*,TYPE_14__*) ; 
 int /*<<< orphan*/  yaml_emitter_initialize (TYPE_14__*) ; 
 int /*<<< orphan*/  yaml_emitter_open (TYPE_14__*) ; 
 int /*<<< orphan*/  yaml_emitter_set_canonical (TYPE_14__*,int) ; 
 int /*<<< orphan*/  yaml_emitter_set_output_file (TYPE_14__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yaml_emitter_set_unicode (TYPE_14__*,int) ; 
 int /*<<< orphan*/  yaml_event_delete (TYPE_14__*) ; 
 int /*<<< orphan*/  yaml_parser_delete (TYPE_14__*) ; 
 int /*<<< orphan*/  yaml_parser_initialize (TYPE_14__*) ; 
 int /*<<< orphan*/  yaml_parser_parse (TYPE_14__*,TYPE_14__*) ; 
 int /*<<< orphan*/  yaml_parser_set_input_file (TYPE_14__*,int /*<<< orphan*/ ) ; 

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
    yaml_event_t input_event;
    yaml_document_t output_document;

    int root;

    /* Clear the objects. */

    memset(&parser, 0, sizeof(parser));
    memset(&emitter, 0, sizeof(emitter));
    memset(&input_event, 0, sizeof(input_event));
    memset(&output_document, 0, sizeof(output_document));

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
        printf("%s <input\n"
                "or\n%s -h | --help\nDeconstruct a YAML stream\n\nOptions:\n"
                "-h, --help\t\tdisplay this help and exit\n"
                "-c, --canonical\t\toutput in the canonical YAML format\n"
                "-u, --unicode\t\toutput unescaped non-ASCII characters\n",
                argv[0], argv[0]);
        return 0;
    }

    /* Initialize the parser and emitter objects. */

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Could not initialize the parser object\n");
        return 1;
    }

    if (!yaml_emitter_initialize(&emitter)) {
        yaml_parser_delete(&parser);
        fprintf(stderr, "Could not inialize the emitter object\n");
        return 1;
    }

    /* Set the parser parameters. */

    yaml_parser_set_input_file(&parser, stdin);

    /* Set the emitter parameters. */

    yaml_emitter_set_output_file(&emitter, stdout);

    yaml_emitter_set_canonical(&emitter, canonical);
    yaml_emitter_set_unicode(&emitter, unicode);

    /* Create and emit the STREAM-START event. */

    if (!yaml_emitter_open(&emitter))
        goto emitter_error;

    /* Create a output_document object. */

    if (!yaml_document_initialize(&output_document, NULL, NULL, NULL, 0, 0))
        goto document_error;

    /* Create the root sequence. */

    root = yaml_document_add_sequence(&output_document, NULL,
            YAML_BLOCK_SEQUENCE_STYLE);
    if (!root) goto document_error;

    /* Loop through the input events. */

    while (!done)
    {
        int properties, key, value, map, seq;

        /* Get the next event. */

        if (!yaml_parser_parse(&parser, &input_event))
            goto parser_error;

        /* Check if this is the stream end. */

        if (input_event.type == YAML_STREAM_END_EVENT) {
            done = 1;
        }

        /* Create a mapping node and attach it to the root sequence. */

        properties = yaml_document_add_mapping(&output_document, NULL,
                YAML_BLOCK_MAPPING_STYLE);
        if (!properties) goto document_error;
        if (!yaml_document_append_sequence_item(&output_document,
                    root, properties)) goto document_error;

        /* Analyze the event. */

        switch (input_event.type)
        {
            case YAML_STREAM_START_EVENT:

                /* Add 'type': 'STREAM-START'. */

                key = yaml_document_add_scalar(&output_document, NULL,
                    "type", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!key) goto document_error;
                value = yaml_document_add_scalar(&output_document, NULL,
                    "STREAM-START", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!value) goto document_error;
                if (!yaml_document_append_mapping_pair(&output_document,
                            properties, key, value)) goto document_error;

                /* Add 'encoding': <encoding>. */

                if (input_event.data.stream_start.encoding)
                {
                    yaml_encoding_t encoding
                        = input_event.data.stream_start.encoding;

                    key = yaml_document_add_scalar(&output_document, NULL,
                        "encoding", -1, YAML_PLAIN_SCALAR_STYLE);
                    if (!key) goto document_error;
                    value = yaml_document_add_scalar(&output_document, NULL,
                            (encoding == YAML_UTF8_ENCODING ? "utf-8" :
                             encoding == YAML_UTF16LE_ENCODING ? "utf-16-le" :
                             encoding == YAML_UTF16BE_ENCODING ? "utf-16-be" :
                             "unknown"), -1, YAML_PLAIN_SCALAR_STYLE);
                    if (!value) goto document_error;
                    if (!yaml_document_append_mapping_pair(&output_document,
                                properties, key, value)) goto document_error;
                }
                    
                break;

            case YAML_STREAM_END_EVENT:

                /* Add 'type': 'STREAM-END'. */

                key = yaml_document_add_scalar(&output_document, NULL,
                    "type", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!key) goto document_error;
                value = yaml_document_add_scalar(&output_document, NULL,
                    "STREAM-END", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!value) goto document_error;
                if (!yaml_document_append_mapping_pair(&output_document,
                            properties, key, value)) goto document_error;

                break;

            case YAML_DOCUMENT_START_EVENT:

                /* Add 'type': 'DOCUMENT-START'. */

                key = yaml_document_add_scalar(&output_document, NULL,
                    "type", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!key) goto document_error;
                value = yaml_document_add_scalar(&output_document, NULL,
                    "DOCUMENT-START", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!value) goto document_error;
                if (!yaml_document_append_mapping_pair(&output_document,
                            properties, key, value)) goto document_error;

                /* Display the output_document version numbers. */

                if (input_event.data.document_start.version_directive)
                {
                    yaml_version_directive_t *version
                        = input_event.data.document_start.version_directive;
                    char number[64];

                    /* Add 'version': {}. */
                    
                    key = yaml_document_add_scalar(&output_document, NULL,
                        "version", -1, YAML_PLAIN_SCALAR_STYLE);
                    if (!key) goto document_error;
                    map = yaml_document_add_mapping(&output_document, NULL,
                            YAML_FLOW_MAPPING_STYLE);
                    if (!map) goto document_error;
                    if (!yaml_document_append_mapping_pair(&output_document,
                                properties, key, map)) goto document_error;

                    /* Add 'major': <number>. */

                    key = yaml_document_add_scalar(&output_document, NULL,
                        "major", -1, YAML_PLAIN_SCALAR_STYLE);
                    if (!key) goto document_error;
                    sprintf(number, "%d", version->major);
                    value = yaml_document_add_scalar(&output_document, YAML_INT_TAG,
                        number, -1, YAML_PLAIN_SCALAR_STYLE);
                    if (!value) goto document_error;
                    if (!yaml_document_append_mapping_pair(&output_document,
                                map, key, value)) goto document_error;

                    /* Add 'minor': <number>. */

                    key = yaml_document_add_scalar(&output_document, NULL,
                        "minor", -1, YAML_PLAIN_SCALAR_STYLE);
                    if (!key) goto document_error;
                    sprintf(number, "%d", version->minor);
                    value = yaml_document_add_scalar(&output_document, YAML_INT_TAG,
                        number, -1, YAML_PLAIN_SCALAR_STYLE);
                    if (!value) goto document_error;
                    if (!yaml_document_append_mapping_pair(&output_document,
                                map, key, value)) goto document_error;
                }

                /* Display the output_document tag directives. */

                if (input_event.data.document_start.tag_directives.start
                        != input_event.data.document_start.tag_directives.end)
                {
                    yaml_tag_directive_t *tag;

                    /* Add 'tags': []. */
                    
                    key = yaml_document_add_scalar(&output_document, NULL,
                        "tags", -1, YAML_PLAIN_SCALAR_STYLE);
                    if (!key) goto document_error;
                    seq = yaml_document_add_sequence(&output_document, NULL,
                            YAML_BLOCK_SEQUENCE_STYLE);
                    if (!seq) goto document_error;
                    if (!yaml_document_append_mapping_pair(&output_document,
                                properties, key, seq)) goto document_error;

                    for (tag = input_event.data.document_start.tag_directives.start;
                            tag != input_event.data.document_start.tag_directives.end;
                            tag ++)
                    {
                        /* Add {}. */

                        map = yaml_document_add_mapping(&output_document, NULL,
                                YAML_FLOW_MAPPING_STYLE);
                        if (!map) goto document_error;
                        if (!yaml_document_append_sequence_item(&output_document,
                                    seq, map)) goto document_error;

                        /* Add 'handle': <handle>. */

                        key = yaml_document_add_scalar(&output_document, NULL,
                            "handle", -1, YAML_PLAIN_SCALAR_STYLE);
                        if (!key) goto document_error;
                        value = yaml_document_add_scalar(&output_document, NULL,
                            tag->handle, -1, YAML_DOUBLE_QUOTED_SCALAR_STYLE);
                        if (!value) goto document_error;
                        if (!yaml_document_append_mapping_pair(&output_document,
                                    map, key, value)) goto document_error;

                        /* Add 'prefix': <prefix>. */

                        key = yaml_document_add_scalar(&output_document, NULL,
                            "prefix", -1, YAML_PLAIN_SCALAR_STYLE);
                        if (!key) goto document_error;
                        value = yaml_document_add_scalar(&output_document, NULL,
                            tag->prefix, -1, YAML_DOUBLE_QUOTED_SCALAR_STYLE);
                        if (!value) goto document_error;
                        if (!yaml_document_append_mapping_pair(&output_document,
                                    map, key, value)) goto document_error;
                    }
                }

                /* Add 'implicit': <flag>. */

                key = yaml_document_add_scalar(&output_document, NULL,
                    "implicit", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!key) goto document_error;
                value = yaml_document_add_scalar(&output_document, YAML_BOOL_TAG,
                        (input_event.data.document_start.implicit ?
                         "true" : "false"), -1, YAML_PLAIN_SCALAR_STYLE);
                if (!value) goto document_error;
                if (!yaml_document_append_mapping_pair(&output_document,
                            properties, key, value)) goto document_error;

                break;

            case YAML_DOCUMENT_END_EVENT:

                /* Add 'type': 'DOCUMENT-END'. */

                key = yaml_document_add_scalar(&output_document, NULL,
                    "type", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!key) goto document_error;
                value = yaml_document_add_scalar(&output_document, NULL,
                    "DOCUMENT-END", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!value) goto document_error;
                if (!yaml_document_append_mapping_pair(&output_document,
                            properties, key, value)) goto document_error;

                /* Add 'implicit': <flag>. */

                key = yaml_document_add_scalar(&output_document, NULL,
                    "implicit", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!key) goto document_error;
                value = yaml_document_add_scalar(&output_document, YAML_BOOL_TAG,
                        (input_event.data.document_end.implicit ?
                         "true" : "false"), -1, YAML_PLAIN_SCALAR_STYLE);
                if (!value) goto document_error;
                if (!yaml_document_append_mapping_pair(&output_document,
                            properties, key, value)) goto document_error;

                break;

            case YAML_ALIAS_EVENT:

                /* Add 'type': 'ALIAS'. */

                key = yaml_document_add_scalar(&output_document, NULL,
                    "type", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!key) goto document_error;
                value = yaml_document_add_scalar(&output_document, NULL,
                    "ALIAS", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!value) goto document_error;
                if (!yaml_document_append_mapping_pair(&output_document,
                            properties, key, value)) goto document_error;

                /* Add 'anchor': <anchor>. */

                key = yaml_document_add_scalar(&output_document, NULL,
                    "anchor", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!key) goto document_error;
                value = yaml_document_add_scalar(&output_document, NULL,
                        input_event.data.alias.anchor, -1,
                        YAML_DOUBLE_QUOTED_SCALAR_STYLE);
                if (!value) goto document_error;
                if (!yaml_document_append_mapping_pair(&output_document,
                            properties, key, value)) goto document_error;

                break;

            case YAML_SCALAR_EVENT:

                /* Add 'type': 'SCALAR'. */

                key = yaml_document_add_scalar(&output_document, NULL,
                    "type", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!key) goto document_error;
                value = yaml_document_add_scalar(&output_document, NULL,
                    "SCALAR", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!value) goto document_error;
                if (!yaml_document_append_mapping_pair(&output_document,
                            properties, key, value)) goto document_error;

                /* Add 'anchor': <anchor>. */

                if (input_event.data.scalar.anchor)
                {
                    key = yaml_document_add_scalar(&output_document, NULL,
                        "anchor", -1, YAML_PLAIN_SCALAR_STYLE);
                    if (!key) goto document_error;
                    value = yaml_document_add_scalar(&output_document, NULL,
                            input_event.data.scalar.anchor, -1,
                            YAML_DOUBLE_QUOTED_SCALAR_STYLE);
                    if (!value) goto document_error;
                    if (!yaml_document_append_mapping_pair(&output_document,
                                properties, key, value)) goto document_error;
                }

                /* Add 'tag': <tag>. */

                if (input_event.data.scalar.tag)
                {
                    key = yaml_document_add_scalar(&output_document, NULL,
                        "tag", -1, YAML_PLAIN_SCALAR_STYLE);
                    if (!key) goto document_error;
                    value = yaml_document_add_scalar(&output_document, NULL,
                            input_event.data.scalar.tag, -1,
                            YAML_DOUBLE_QUOTED_SCALAR_STYLE);
                    if (!value) goto document_error;
                    if (!yaml_document_append_mapping_pair(&output_document,
                                properties, key, value)) goto document_error;
                }

                /* Add 'value': <value>. */

                key = yaml_document_add_scalar(&output_document, NULL,
                    "value", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!key) goto document_error;
                value = yaml_document_add_scalar(&output_document, NULL,
                        input_event.data.scalar.value,
                        input_event.data.scalar.length,
                        YAML_DOUBLE_QUOTED_SCALAR_STYLE);
                if (!value) goto document_error;
                if (!yaml_document_append_mapping_pair(&output_document,
                            properties, key, value)) goto document_error;

                /* Display if the scalar tag is implicit. */

                /* Add 'implicit': {} */

                key = yaml_document_add_scalar(&output_document, NULL,
                    "version", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!key) goto document_error;
                map = yaml_document_add_mapping(&output_document, NULL,
                        YAML_FLOW_MAPPING_STYLE);
                if (!map) goto document_error;
                if (!yaml_document_append_mapping_pair(&output_document,
                            properties, key, map)) goto document_error;

                /* Add 'plain': <flag>. */

                key = yaml_document_add_scalar(&output_document, NULL,
                    "plain", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!key) goto document_error;
                value = yaml_document_add_scalar(&output_document, YAML_BOOL_TAG,
                        (input_event.data.scalar.plain_implicit ?
                         "true" : "false"), -1, YAML_PLAIN_SCALAR_STYLE);
                if (!value) goto document_error;
                if (!yaml_document_append_mapping_pair(&output_document,
                            map, key, value)) goto document_error;

                /* Add 'quoted': <flag>. */

                key = yaml_document_add_scalar(&output_document, NULL,
                    "quoted", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!key) goto document_error;
                value = yaml_document_add_scalar(&output_document, YAML_BOOL_TAG,
                        (input_event.data.scalar.quoted_implicit ?
                         "true" : "false"), -1, YAML_PLAIN_SCALAR_STYLE);
                if (!value) goto document_error;
                if (!yaml_document_append_mapping_pair(&output_document,
                            map, key, value)) goto document_error;

                /* Display the style information. */

                if (input_event.data.scalar.style)
                {
                    yaml_scalar_style_t style = input_event.data.scalar.style;

                    /* Add 'style': <style>. */

                    key = yaml_document_add_scalar(&output_document, NULL,
                        "style", -1, YAML_PLAIN_SCALAR_STYLE);
                    if (!key) goto document_error;
                    value = yaml_document_add_scalar(&output_document, NULL,
                            (style == YAML_PLAIN_SCALAR_STYLE ? "plain" :
                             style == YAML_SINGLE_QUOTED_SCALAR_STYLE ?
                                    "single-quoted" :
                             style == YAML_DOUBLE_QUOTED_SCALAR_STYLE ?
                                    "double-quoted" :
                             style == YAML_LITERAL_SCALAR_STYLE ? "literal" :
                             style == YAML_FOLDED_SCALAR_STYLE ? "folded" :
                             "unknown"), -1, YAML_PLAIN_SCALAR_STYLE);
                    if (!value) goto document_error;
                    if (!yaml_document_append_mapping_pair(&output_document,
                                properties, key, value)) goto document_error;
                }

                break;

            case YAML_SEQUENCE_START_EVENT:

                /* Add 'type': 'SEQUENCE-START'. */

                key = yaml_document_add_scalar(&output_document, NULL,
                    "type", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!key) goto document_error;
                value = yaml_document_add_scalar(&output_document, NULL,
                    "SEQUENCE-START", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!value) goto document_error;
                if (!yaml_document_append_mapping_pair(&output_document,
                            properties, key, value)) goto document_error;

                /* Add 'anchor': <anchor>. */

                if (input_event.data.sequence_start.anchor)
                {
                    key = yaml_document_add_scalar(&output_document, NULL,
                        "anchor", -1, YAML_PLAIN_SCALAR_STYLE);
                    if (!key) goto document_error;
                    value = yaml_document_add_scalar(&output_document, NULL,
                            input_event.data.sequence_start.anchor, -1,
                            YAML_DOUBLE_QUOTED_SCALAR_STYLE);
                    if (!value) goto document_error;
                    if (!yaml_document_append_mapping_pair(&output_document,
                                properties, key, value)) goto document_error;
                }

                /* Add 'tag': <tag>. */

                if (input_event.data.sequence_start.tag)
                {
                    key = yaml_document_add_scalar(&output_document, NULL,
                        "tag", -1, YAML_PLAIN_SCALAR_STYLE);
                    if (!key) goto document_error;
                    value = yaml_document_add_scalar(&output_document, NULL,
                            input_event.data.sequence_start.tag, -1,
                            YAML_DOUBLE_QUOTED_SCALAR_STYLE);
                    if (!value) goto document_error;
                    if (!yaml_document_append_mapping_pair(&output_document,
                                properties, key, value)) goto document_error;
                }

                /* Add 'implicit': <flag>. */

                key = yaml_document_add_scalar(&output_document, NULL,
                    "implicit", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!key) goto document_error;
                value = yaml_document_add_scalar(&output_document, YAML_BOOL_TAG,
                        (input_event.data.sequence_start.implicit ?
                         "true" : "false"), -1, YAML_PLAIN_SCALAR_STYLE);
                if (!value) goto document_error;
                if (!yaml_document_append_mapping_pair(&output_document,
                            properties, key, value)) goto document_error;

                /* Display the style information. */

                if (input_event.data.sequence_start.style)
                {
                    yaml_sequence_style_t style
                        = input_event.data.sequence_start.style;

                    /* Add 'style': <style>. */

                    key = yaml_document_add_scalar(&output_document, NULL,
                        "style", -1, YAML_PLAIN_SCALAR_STYLE);
                    if (!key) goto document_error;
                    value = yaml_document_add_scalar(&output_document, NULL,
                            (style == YAML_BLOCK_SEQUENCE_STYLE ? "block" :
                             style == YAML_FLOW_SEQUENCE_STYLE ? "flow" :
                             "unknown"), -1, YAML_PLAIN_SCALAR_STYLE);
                    if (!value) goto document_error;
                    if (!yaml_document_append_mapping_pair(&output_document,
                                properties, key, value)) goto document_error;
                }

                break;

            case YAML_SEQUENCE_END_EVENT:

                /* Add 'type': 'SEQUENCE-END'. */

                key = yaml_document_add_scalar(&output_document, NULL,
                    "type", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!key) goto document_error;
                value = yaml_document_add_scalar(&output_document, NULL,
                    "SEQUENCE-END", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!value) goto document_error;
                if (!yaml_document_append_mapping_pair(&output_document,
                            properties, key, value)) goto document_error;

                break;

            case YAML_MAPPING_START_EVENT:

                /* Add 'type': 'MAPPING-START'. */

                key = yaml_document_add_scalar(&output_document, NULL,
                    "type", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!key) goto document_error;
                value = yaml_document_add_scalar(&output_document, NULL,
                    "MAPPING-START", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!value) goto document_error;
                if (!yaml_document_append_mapping_pair(&output_document,
                            properties, key, value)) goto document_error;

                /* Add 'anchor': <anchor>. */

                if (input_event.data.mapping_start.anchor)
                {
                    key = yaml_document_add_scalar(&output_document, NULL,
                        "anchor", -1, YAML_PLAIN_SCALAR_STYLE);
                    if (!key) goto document_error;
                    value = yaml_document_add_scalar(&output_document, NULL,
                            input_event.data.mapping_start.anchor, -1,
                            YAML_DOUBLE_QUOTED_SCALAR_STYLE);
                    if (!value) goto document_error;
                    if (!yaml_document_append_mapping_pair(&output_document,
                                properties, key, value)) goto document_error;
                }

                /* Add 'tag': <tag>. */

                if (input_event.data.mapping_start.tag)
                {
                    key = yaml_document_add_scalar(&output_document, NULL,
                        "tag", -1, YAML_PLAIN_SCALAR_STYLE);
                    if (!key) goto document_error;
                    value = yaml_document_add_scalar(&output_document, NULL,
                            input_event.data.mapping_start.tag, -1,
                            YAML_DOUBLE_QUOTED_SCALAR_STYLE);
                    if (!value) goto document_error;
                    if (!yaml_document_append_mapping_pair(&output_document,
                                properties, key, value)) goto document_error;
                }

                /* Add 'implicit': <flag>. */

                key = yaml_document_add_scalar(&output_document, NULL,
                    "implicit", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!key) goto document_error;
                value = yaml_document_add_scalar(&output_document, YAML_BOOL_TAG,
                        (input_event.data.mapping_start.implicit ?
                         "true" : "false"), -1, YAML_PLAIN_SCALAR_STYLE);
                if (!value) goto document_error;
                if (!yaml_document_append_mapping_pair(&output_document,
                            properties, key, value)) goto document_error;

                /* Display the style information. */

                if (input_event.data.sequence_start.style)
                {
                    yaml_sequence_style_t style
                        = input_event.data.mapping_start.style;

                    /* Add 'style': <style>. */

                    key = yaml_document_add_scalar(&output_document, NULL,
                        "style", -1, YAML_PLAIN_SCALAR_STYLE);
                    if (!key) goto document_error;
                    value = yaml_document_add_scalar(&output_document, NULL,
                            (style == YAML_BLOCK_MAPPING_STYLE ? "block" :
                             style == YAML_FLOW_MAPPING_STYLE ? "flow" :
                             "unknown"), -1, YAML_PLAIN_SCALAR_STYLE);
                    if (!value) goto document_error;
                    if (!yaml_document_append_mapping_pair(&output_document,
                                properties, key, value)) goto document_error;
                }

                break;

            case YAML_MAPPING_END_EVENT:

                /* Add 'type': 'MAPPING-END'. */

                key = yaml_document_add_scalar(&output_document, NULL,
                    "type", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!key) goto document_error;
                value = yaml_document_add_scalar(&output_document, NULL,
                    "MAPPING-END", -1, YAML_PLAIN_SCALAR_STYLE);
                if (!value) goto document_error;
                if (!yaml_document_append_mapping_pair(&output_document,
                            properties, key, value)) goto document_error;

                break;

            default:
                /* It couldn't really happen. */
                break;
        }

        /* Delete the event object. */

        yaml_event_delete(&input_event);
    }

    if (!yaml_emitter_dump(&emitter, &output_document))
        goto emitter_error;
    if (!yaml_emitter_close(&emitter))
        goto emitter_error;

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

        default:
            /* Couldn't happen. */
            fprintf(stderr, "Internal error\n");
            break;
    }

    yaml_event_delete(&input_event);
    yaml_document_delete(&output_document);
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

    yaml_event_delete(&input_event);
    yaml_document_delete(&output_document);
    yaml_parser_delete(&parser);
    yaml_emitter_delete(&emitter);

    return 1;

document_error:

    fprintf(stderr, "Memory error: Not enough memory for creating a document\n");

    yaml_event_delete(&input_event);
    yaml_document_delete(&output_document);
    yaml_parser_delete(&parser);
    yaml_emitter_delete(&emitter);

    return 1;
}