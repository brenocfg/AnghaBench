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
typedef  int /*<<< orphan*/  ucl_object_t ;
typedef  scalar_t__ ucl_emitter_t ;
struct ucl_schema_error {char* msg; } ;
struct ucl_parser {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t BUFSIZ ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ UCL_EMIT_CONFIG ; 
 scalar_t__ UCL_EMIT_JSON ; 
 scalar_t__ UCL_EMIT_JSON_COMPACT ; 
 scalar_t__ UCL_EMIT_MSGPACK ; 
 scalar_t__ UCL_EMIT_YAML ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ fread (unsigned char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (unsigned char*,int,size_t,int /*<<< orphan*/ *) ; 
 char getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned char* malloc (size_t) ; 
 char* optarg ; 
 int /*<<< orphan*/  opts ; 
 int /*<<< orphan*/  perror (char*) ; 
 unsigned char* realloc (unsigned char*,size_t) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* ucl_object_emit (int /*<<< orphan*/ *,scalar_t__) ; 
 unsigned char* ucl_object_emit_len (int /*<<< orphan*/ *,scalar_t__,size_t*) ; 
 int /*<<< orphan*/  ucl_object_validate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ucl_schema_error*) ; 
 int /*<<< orphan*/  ucl_parser_add_chunk (struct ucl_parser*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  ucl_parser_add_file (struct ucl_parser*,char const*) ; 
 char* ucl_parser_get_error (struct ucl_parser*) ; 
 int /*<<< orphan*/ * ucl_parser_get_object (struct ucl_parser*) ; 
 struct ucl_parser* ucl_parser_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*,int /*<<< orphan*/ *) ; 

int main(int argc, char **argv) {
  char ch;
  FILE *in = stdin, *out = stdout;
  const char *schema = NULL;
  unsigned char *buf = NULL;
  size_t size = 0, r = 0;
  struct ucl_parser *parser = NULL;
  ucl_object_t *obj = NULL;
  ucl_emitter_t emitter = UCL_EMIT_CONFIG;

  while((ch = getopt_long(argc, argv, "hi:o:s:f:", opts, NULL)) != -1) {
    switch (ch) {
    case 'i':
      in = fopen(optarg, "r");
      if (in == NULL) {
        perror("fopen on input file");
        exit(EXIT_FAILURE);
      }
      break;
    case 'o':
      out = fopen(optarg, "w");
      if (out == NULL) {
        perror("fopen on output file");
        exit(EXIT_FAILURE);
      }
      break;
    case 's':
      schema = optarg;
      break;
    case 'f':
      if (strcmp(optarg, "ucl") == 0) {
        emitter = UCL_EMIT_CONFIG;
      } else if (strcmp(optarg, "json") == 0) {
        emitter = UCL_EMIT_JSON;
      } else if (strcmp(optarg, "yaml") == 0) {
        emitter = UCL_EMIT_YAML;
      } else if (strcmp(optarg, "compact_json") == 0) {
        emitter = UCL_EMIT_JSON_COMPACT;
      } else if (strcmp(optarg, "msgpack") == 0) {
        emitter = UCL_EMIT_MSGPACK;
      } else {
        fprintf(stderr, "Unknown output format: %s\n", optarg);
        exit(EXIT_FAILURE);
      }
      break;
    case 'h':
      usage(argv[0], stdout);
      exit(0);
    default:
      usage(argv[0], stderr);
      exit(EXIT_FAILURE);
      break;
    }
  }

  parser = ucl_parser_new(0);
  buf = malloc(BUFSIZ);
  size = BUFSIZ;
  while(!feof(in) && !ferror(in)) {
    if (r == size) {
      buf = realloc(buf, size*2);
      size *= 2;
      if (buf == NULL) {
        perror("realloc");
        exit(EXIT_FAILURE);
      }
    }
    r += fread(buf + r, 1, size - r, in);
  }
  if (ferror(in)) {
    fprintf(stderr, "Failed to read the input file.\n");
    exit(EXIT_FAILURE);
  }
  fclose(in);
  if (!ucl_parser_add_chunk(parser, buf, r)) {
    fprintf(stderr, "Failed to parse input file: %s\n",
            ucl_parser_get_error(parser));
    exit(EXIT_FAILURE);
  }
  if ((obj = ucl_parser_get_object(parser)) == NULL) {
    fprintf(stderr, "Failed to get root object: %s\n",
            ucl_parser_get_error(parser));
    exit(EXIT_FAILURE);
  }
  if (schema != NULL) {
    struct ucl_parser *schema_parser = ucl_parser_new(0);
    ucl_object_t *schema_obj = NULL;
    struct ucl_schema_error error;

    if (!ucl_parser_add_file(schema_parser, schema)) {
      fprintf(stderr, "Failed to parse schema file: %s\n",
              ucl_parser_get_error(schema_parser));
      exit(EXIT_FAILURE);
    }
    if ((schema_obj = ucl_parser_get_object(schema_parser)) == NULL) {
      fprintf(stderr, "Failed to get root object: %s\n",
              ucl_parser_get_error(schema_parser));
      exit(EXIT_FAILURE);
    }
    if (!ucl_object_validate(schema_obj, obj, &error)) {
      fprintf(stderr, "Validation failed: %s\n", error.msg);
      exit(EXIT_FAILURE);
    }
  }

  if (emitter != UCL_EMIT_MSGPACK) {
    fprintf(out, "%s\n", ucl_object_emit(obj, emitter));
  }
  else {
    size_t len;
    unsigned char *res;

    res = ucl_object_emit_len(obj, emitter, &len);
    fwrite(res, 1, len, out);
  }

  return 0;
}