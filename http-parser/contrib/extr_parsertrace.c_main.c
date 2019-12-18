#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  settings ;
struct TYPE_4__ {int /*<<< orphan*/  on_message_complete; int /*<<< orphan*/  on_body; int /*<<< orphan*/  on_headers_complete; int /*<<< orphan*/  on_header_value; int /*<<< orphan*/  on_header_field; int /*<<< orphan*/  on_url; int /*<<< orphan*/  on_message_begin; } ;
typedef  TYPE_1__ http_parser_settings ;
typedef  int /*<<< orphan*/  http_parser ;
typedef  enum http_parser_type { ____Placeholder_http_parser_type } http_parser_type ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int HTTP_BOTH ; 
 int /*<<< orphan*/  HTTP_PARSER_ERRNO (int /*<<< orphan*/ *) ; 
 int HTTP_REQUEST ; 
 int HTTP_RESPONSE ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t fread (char*,int,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 char* http_errno_description (int /*<<< orphan*/ ) ; 
 char* http_errno_name (int /*<<< orphan*/ ) ; 
 size_t http_parser_execute (int /*<<< orphan*/ *,TYPE_1__*,char*,long) ; 
 int /*<<< orphan*/  http_parser_init (int /*<<< orphan*/ *,int) ; 
 char* malloc (long) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  on_body ; 
 int /*<<< orphan*/  on_header_field ; 
 int /*<<< orphan*/  on_header_value ; 
 int /*<<< orphan*/  on_headers_complete ; 
 int /*<<< orphan*/  on_message_begin ; 
 int /*<<< orphan*/  on_message_complete ; 
 int /*<<< orphan*/  on_url ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char* argv[]) {
  enum http_parser_type file_type;

  if (argc != 3) {
    usage(argv[0]);
  }

  char* type = argv[1];
  if (type[0] != '-') {
    usage(argv[0]);
  }

  switch (type[1]) {
    /* in the case of "-", type[1] will be NUL */
    case 'r':
      file_type = HTTP_RESPONSE;
      break;
    case 'q':
      file_type = HTTP_REQUEST;
      break;
    case 'b':
      file_type = HTTP_BOTH;
      break;
    default:
      usage(argv[0]);
  }

  char* filename = argv[2];
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    perror("fopen");
    goto fail;
  }

  fseek(file, 0, SEEK_END);
  long file_length = ftell(file);
  if (file_length == -1) {
    perror("ftell");
    goto fail;
  }
  fseek(file, 0, SEEK_SET);

  char* data = malloc(file_length);
  if (fread(data, 1, file_length, file) != (size_t)file_length) {
    fprintf(stderr, "couldn't read entire file\n");
    free(data);
    goto fail;
  }

  http_parser_settings settings;
  memset(&settings, 0, sizeof(settings));
  settings.on_message_begin = on_message_begin;
  settings.on_url = on_url;
  settings.on_header_field = on_header_field;
  settings.on_header_value = on_header_value;
  settings.on_headers_complete = on_headers_complete;
  settings.on_body = on_body;
  settings.on_message_complete = on_message_complete;

  http_parser parser;
  http_parser_init(&parser, file_type);
  size_t nparsed = http_parser_execute(&parser, &settings, data, file_length);
  free(data);

  if (nparsed != (size_t)file_length) {
    fprintf(stderr,
            "Error: %s (%s)\n",
            http_errno_description(HTTP_PARSER_ERRNO(&parser)),
            http_errno_name(HTTP_PARSER_ERRNO(&parser)));
    goto fail;
  }

  return EXIT_SUCCESS;

fail:
  fclose(file);
  return EXIT_FAILURE;
}