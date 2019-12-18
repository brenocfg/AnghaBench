#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  yaml_parser_t ;
typedef  int /*<<< orphan*/  yaml_document_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  yaml_document_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yaml_document_get_root_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yaml_parser_delete (int /*<<< orphan*/ *) ; 
 int yaml_parser_initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yaml_parser_load (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yaml_parser_set_input_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
main(int argc, char *argv[])
{
    int number;

    if (argc < 2) {
        printf("Usage: %s file1.yaml ...\n", argv[0]);
        return 0;
    }

    for (number = 1; number < argc; number ++)
    {
        FILE *file;
        yaml_parser_t parser;
        yaml_document_t document;
        int done = 0;
        int count = 0;
        int error = 0;

        printf("[%d] Loading '%s': ", number, argv[number]);
        fflush(stdout);

        file = fopen(argv[number], "rb");
        assert(file);

        assert(yaml_parser_initialize(&parser));

        yaml_parser_set_input_file(&parser, file);

        while (!done)
        {
            if (!yaml_parser_load(&parser, &document)) {
                error = 1;
                break;
            }

            done = (!yaml_document_get_root_node(&document));

            yaml_document_delete(&document);

            if (!done) count ++;
        }

        yaml_parser_delete(&parser);

        assert(!fclose(file));

        printf("%s (%d documents)\n", (error ? "FAILURE" : "SUCCESS"), count);
    }

    return 0;
}