#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int iterator; scalar_t__ input_count; char const* current_input_path; int* not_input_indices; size_t ignore; int argc; char** argv; char* suffix; scalar_t__ modified_path; void* iterator_error; scalar_t__ decompress; scalar_t__ current_output_path; scalar_t__ write_to_stdout; scalar_t__ output_path; } ;
typedef  TYPE_1__ Context ;
typedef  void* BROTLI_BOOL ;

/* Variables and functions */
 void* BROTLI_FALSE ; 
 void* BROTLI_TRUE ; 
 scalar_t__ FileName (scalar_t__) ; 
 char* PrintablePath (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (scalar_t__,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static BROTLI_BOOL NextFile(Context* context) {
  const char* arg;
  size_t arg_len;

  /* Iterator points to last used arg; increment to search for the next one. */
  context->iterator++;

  /* No input path; read from console. */
  if (context->input_count == 0) {
    if (context->iterator > 1) return BROTLI_FALSE;
    context->current_input_path = NULL;
    /* Either write to the specified path, or to console. */
    context->current_output_path = context->output_path;
    return BROTLI_TRUE;
  }

  /* Skip option arguments. */
  while (context->iterator == context->not_input_indices[context->ignore]) {
    context->iterator++;
    context->ignore++;
  }

  /* All args are scanned already. */
  if (context->iterator >= context->argc) return BROTLI_FALSE;

  /* Iterator now points to the input file name. */
  arg = context->argv[context->iterator];
  arg_len = strlen(arg);
  /* Read from console. */
  if (arg_len == 1 && arg[0] == '-') {
    context->current_input_path = NULL;
    context->current_output_path = context->output_path;
    return BROTLI_TRUE;
  }

  context->current_input_path = arg;
  context->current_output_path = context->output_path;

  if (context->output_path) return BROTLI_TRUE;
  if (context->write_to_stdout) return BROTLI_TRUE;

  strcpy(context->modified_path, arg);
  context->current_output_path = context->modified_path;
  /* If output is not specified, input path suffix should match. */
  if (context->decompress) {
    size_t suffix_len = strlen(context->suffix);
    char* name = (char*)FileName(context->modified_path);
    char* name_suffix;
    size_t name_len = strlen(name);
    if (name_len < suffix_len + 1) {
      fprintf(stderr, "empty output file name for [%s] input file\n",
              PrintablePath(arg));
      context->iterator_error = BROTLI_TRUE;
      return BROTLI_FALSE;
    }
    name_suffix = name + name_len - suffix_len;
    if (strcmp(context->suffix, name_suffix) != 0) {
      fprintf(stderr, "input file [%s] suffix mismatch\n",
              PrintablePath(arg));
      context->iterator_error = BROTLI_TRUE;
      return BROTLI_FALSE;
    }
    name_suffix[0] = 0;
    return BROTLI_TRUE;
  } else {
    strcpy(context->modified_path + arg_len, context->suffix);
    return BROTLI_TRUE;
  }
}