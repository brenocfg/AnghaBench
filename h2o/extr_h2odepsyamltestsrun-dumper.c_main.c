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
typedef  int /*<<< orphan*/  yaml_emitter_t ;
typedef  unsigned char yaml_document_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFFER_SIZE ; 
 int MAX_DOCUMENTS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ compare_documents (unsigned char*,unsigned char*) ; 
 int copy_document (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  memmove (char**,char**,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ print_output (char*,unsigned char*,size_t,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  yaml_document_delete (unsigned char*) ; 
 int /*<<< orphan*/  yaml_document_get_root_node (unsigned char*) ; 
 int /*<<< orphan*/  yaml_emitter_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yaml_emitter_delete (int /*<<< orphan*/ *) ; 
 scalar_t__ yaml_emitter_dump (int /*<<< orphan*/ *,unsigned char*) ; 
 scalar_t__ yaml_emitter_flush (int /*<<< orphan*/ *) ; 
 int yaml_emitter_initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yaml_emitter_open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yaml_emitter_set_canonical (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  yaml_emitter_set_output_string (int /*<<< orphan*/ *,unsigned char*,int,size_t*) ; 
 int /*<<< orphan*/  yaml_emitter_set_unicode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  yaml_parser_delete (int /*<<< orphan*/ *) ; 
 int yaml_parser_initialize (int /*<<< orphan*/ *) ; 
 scalar_t__ yaml_parser_load (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  yaml_parser_set_input_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yaml_parser_set_input_string (int /*<<< orphan*/ *,unsigned char*,size_t) ; 

int
main(int argc, char *argv[])
{
    int number;
    int canonical = 0;
    int unicode = 0;

    number = 1;
    while (number < argc) {
        if (strcmp(argv[number], "-c") == 0) {
            canonical = 1;
        }
        else if (strcmp(argv[number], "-u") == 0) {
            unicode = 1;
        }
        else if (argv[number][0] == '-') {
            printf("Unknown option: '%s'\n", argv[number]);
            return 0;
        }
        if (argv[number][0] == '-') {
            if (number < argc-1) {
                memmove(argv+number, argv+number+1, (argc-number-1)*sizeof(char *));
            }
            argc --;
        }
        else {
            number ++;
        }
    }

    if (argc < 2) {
        printf("Usage: %s [-c] [-u] file1.yaml ...\n", argv[0]);
        return 0;
    }

    for (number = 1; number < argc; number ++)
    {
        FILE *file;
        yaml_parser_t parser;
        yaml_emitter_t emitter;

        yaml_document_t document;
        unsigned char buffer[BUFFER_SIZE+1];
        size_t written = 0;
        yaml_document_t documents[MAX_DOCUMENTS];
        size_t document_number = 0;
        int done = 0;
        int count = 0;
        int error = 0;
        int k;
        memset(buffer, 0, BUFFER_SIZE+1);
        memset(documents, 0, MAX_DOCUMENTS*sizeof(yaml_document_t));

        printf("[%d] Loading, dumping, and loading again '%s': ", number, argv[number]);
        fflush(stdout);

        file = fopen(argv[number], "rb");
        assert(file);

        assert(yaml_parser_initialize(&parser));
        yaml_parser_set_input_file(&parser, file);
        assert(yaml_emitter_initialize(&emitter));
        if (canonical) {
            yaml_emitter_set_canonical(&emitter, 1);
        }
        if (unicode) {
            yaml_emitter_set_unicode(&emitter, 1);
        }
        yaml_emitter_set_output_string(&emitter, buffer, BUFFER_SIZE, &written);
        yaml_emitter_open(&emitter);

        while (!done)
        {
            if (!yaml_parser_load(&parser, &document)) {
                error = 1;
                break;
            }

            done = (!yaml_document_get_root_node(&document));
            if (!done) {
                assert(document_number < MAX_DOCUMENTS);
                assert(copy_document(&(documents[document_number++]), &document));
                assert(yaml_emitter_dump(&emitter, &document) || 
                        (yaml_emitter_flush(&emitter) && print_output(argv[number], buffer, written, count)));
                count ++;
            }
            else {
                yaml_document_delete(&document);
            }
        }

        yaml_parser_delete(&parser);
        assert(!fclose(file));
        yaml_emitter_close(&emitter);
        yaml_emitter_delete(&emitter);

        if (!error)
        {
            count = done = 0;
            assert(yaml_parser_initialize(&parser));
            yaml_parser_set_input_string(&parser, buffer, written);

            while (!done)
            {
                assert(yaml_parser_load(&parser, &document) || print_output(argv[number], buffer, written, count));
                done = (!yaml_document_get_root_node(&document));
                if (!done) {
                    assert(compare_documents(documents+count, &document) || print_output(argv[number], buffer, written, count));
                    count ++;
                }
                yaml_document_delete(&document);
            }
            yaml_parser_delete(&parser);
        }

        for (k = 0; k < document_number; k ++) {
            yaml_document_delete(documents+k);
        }

        printf("PASSED (length: %d)\n", written);
        print_output(argv[number], buffer, written, -1);
    }

    return 0;
}