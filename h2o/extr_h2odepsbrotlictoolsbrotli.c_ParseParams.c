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
struct TYPE_3__ {int argc; char** argv; int* not_input_indices; char quality; char* output_path; scalar_t__ lgwin; char* suffix; size_t input_count; size_t longest_path_len; int decompress; int test_integrity; void* write_to_stdout; void* verbose; void* junk_source; void* copy_stat; void* force_overwrite; } ;
typedef  TYPE_1__ Context ;
typedef  scalar_t__ Command ;
typedef  void* BROTLI_BOOL ;

/* Variables and functions */
 void* BROTLI_FALSE ; 
 int /*<<< orphan*/  BROTLI_MAX_QUALITY ; 
 int /*<<< orphan*/  BROTLI_MAX_WINDOW_BITS ; 
 int /*<<< orphan*/  BROTLI_MIN_QUALITY ; 
 scalar_t__ BROTLI_MIN_WINDOW_BITS ; 
 void* BROTLI_TRUE ; 
 scalar_t__ COMMAND_DECOMPRESS ; 
 scalar_t__ COMMAND_HELP ; 
 scalar_t__ COMMAND_INVALID ; 
 scalar_t__ COMMAND_TEST_INTEGRITY ; 
 scalar_t__ COMMAND_VERSION ; 
 int MAX_OPTIONS ; 
 scalar_t__ ParseAlias (char*) ; 
 void* ParseInt (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 void* TO_BROTLI_BOOL (int) ; 
 scalar_t__ strchr (char const*,char) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,size_t) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static Command ParseParams(Context* params) {
  int argc = params->argc;
  char** argv = params->argv;
  int i;
  int next_option_index = 0;
  size_t input_count = 0;
  size_t longest_path_len = 1;
  BROTLI_BOOL command_set = BROTLI_FALSE;
  BROTLI_BOOL quality_set = BROTLI_FALSE;
  BROTLI_BOOL output_set = BROTLI_FALSE;
  BROTLI_BOOL keep_set = BROTLI_FALSE;
  BROTLI_BOOL lgwin_set = BROTLI_FALSE;
  BROTLI_BOOL suffix_set = BROTLI_FALSE;
  BROTLI_BOOL after_dash_dash = BROTLI_FALSE;
  Command command = ParseAlias(argv[0]);

  for (i = 1; i < argc; ++i) {
    const char* arg = argv[i];
    /* C99 5.1.2.2.1: "members argv[0] through argv[argc-1] inclusive shall
       contain pointers to strings"; NULL and 0-length are not forbidden. */
    size_t arg_len = arg ? strlen(arg) : 0;

    if (arg_len == 0) {
      params->not_input_indices[next_option_index++] = i;
      continue;
    }

    /* Too many options. The expected longest option list is:
       "-q 0 -w 10 -o f -D d -S b -d -f -k -n -v --", i.e. 16 items in total.
       This check is an additinal guard that is never triggered, but provides an
       additional guard for future changes. */
    if (next_option_index > (MAX_OPTIONS - 2)) {
      return COMMAND_INVALID;
    }

    /* Input file entry. */
    if (after_dash_dash || arg[0] != '-' || arg_len == 1) {
      input_count++;
      if (longest_path_len < arg_len) longest_path_len = arg_len;
      continue;
    }

    /* Not a file entry. */
    params->not_input_indices[next_option_index++] = i;

    /* '--' entry stop parsing arguments. */
    if (arg_len == 2 && arg[1] == '-') {
      after_dash_dash = BROTLI_TRUE;
      continue;
    }

    /* Simple / coalesced options. */
    if (arg[1] != '-') {
      size_t j;
      for (j = 1; j < arg_len; ++j) {
        char c = arg[j];
        if (c >= '0' && c <= '9') {
          if (quality_set) return COMMAND_INVALID;
          quality_set = BROTLI_TRUE;
          params->quality = c - '0';
          continue;
        } else if (c == 'c') {
          if (output_set) return COMMAND_INVALID;
          output_set = BROTLI_TRUE;
          params->write_to_stdout = BROTLI_TRUE;
          continue;
        } else if (c == 'd') {
          if (command_set) return COMMAND_INVALID;
          command_set = BROTLI_TRUE;
          command = COMMAND_DECOMPRESS;
          continue;
        } else if (c == 'f') {
          if (params->force_overwrite) return COMMAND_INVALID;
          params->force_overwrite = BROTLI_TRUE;
          continue;
        } else if (c == 'h') {
          /* Don't parse further. */
          return COMMAND_HELP;
        } else if (c == 'j' || c == 'k') {
          if (keep_set) return COMMAND_INVALID;
          keep_set = BROTLI_TRUE;
          params->junk_source = TO_BROTLI_BOOL(c == 'j');
          continue;
        } else if (c == 'n') {
          if (!params->copy_stat) return COMMAND_INVALID;
          params->copy_stat = BROTLI_FALSE;
          continue;
        } else if (c == 't') {
          if (command_set) return COMMAND_INVALID;
          command_set = BROTLI_TRUE;
          command = COMMAND_TEST_INTEGRITY;
          continue;
        } else if (c == 'v') {
          if (params->verbose) return COMMAND_INVALID;
          params->verbose = BROTLI_TRUE;
          continue;
        } else if (c == 'V') {
          /* Don't parse further. */
          return COMMAND_VERSION;
        } else if (c == 'Z') {
          if (quality_set) return COMMAND_INVALID;
          quality_set = BROTLI_TRUE;
          params->quality = 11;
          continue;
        }
        /* o/q/w/D/S with parameter is expected */
        if (c != 'o' && c != 'q' && c != 'w' && c != 'D' && c != 'S') {
          return COMMAND_INVALID;
        }
        if (j + 1 != arg_len) return COMMAND_INVALID;
        i++;
        if (i == argc || !argv[i] || argv[i][0] == 0) return COMMAND_INVALID;
        params->not_input_indices[next_option_index++] = i;
        if (c == 'o') {
          if (output_set) return COMMAND_INVALID;
          params->output_path = argv[i];
        } else if (c == 'q') {
          if (quality_set) return COMMAND_INVALID;
          quality_set = ParseInt(argv[i], BROTLI_MIN_QUALITY,
                                 BROTLI_MAX_QUALITY, &params->quality);
          if (!quality_set) return COMMAND_INVALID;
        } else if (c == 'w') {
          if (lgwin_set) return COMMAND_INVALID;
          lgwin_set = ParseInt(argv[i], 0,
                               BROTLI_MAX_WINDOW_BITS, &params->lgwin);
          if (!lgwin_set) return COMMAND_INVALID;
          if (params->lgwin != 0 && params->lgwin < BROTLI_MIN_WINDOW_BITS) {
            return COMMAND_INVALID;
          }
        } else if (c == 'S') {
          if (suffix_set) return COMMAND_INVALID;
          suffix_set = BROTLI_TRUE;
          params->suffix = argv[i];
        }
      }
    } else {  /* Double-dash. */
      arg = &arg[2];
      if (strcmp("best", arg) == 0) {
        if (quality_set) return COMMAND_INVALID;
        quality_set = BROTLI_TRUE;
        params->quality = 11;
      } else if (strcmp("decompress", arg) == 0) {
        if (command_set) return COMMAND_INVALID;
        command_set = BROTLI_TRUE;
        command = COMMAND_DECOMPRESS;
      } else if (strcmp("force", arg) == 0) {
        if (params->force_overwrite) return COMMAND_INVALID;
        params->force_overwrite = BROTLI_TRUE;
      } else if (strcmp("help", arg) == 0) {
        /* Don't parse further. */
        return COMMAND_HELP;
      } else if (strcmp("keep", arg) == 0) {
        if (keep_set) return COMMAND_INVALID;
        keep_set = BROTLI_TRUE;
        params->junk_source = BROTLI_FALSE;
      } else if (strcmp("no-copy-stat", arg) == 0) {
        if (!params->copy_stat) return COMMAND_INVALID;
        params->copy_stat = BROTLI_FALSE;
      } else if (strcmp("rm", arg) == 0) {
        if (keep_set) return COMMAND_INVALID;
        keep_set = BROTLI_TRUE;
        params->junk_source = BROTLI_TRUE;
      } else if (strcmp("stdout", arg) == 0) {
        if (output_set) return COMMAND_INVALID;
        output_set = BROTLI_TRUE;
        params->write_to_stdout = BROTLI_TRUE;
      } else if (strcmp("test", arg) == 0) {
        if (command_set) return COMMAND_INVALID;
        command_set = BROTLI_TRUE;
        command = COMMAND_TEST_INTEGRITY;
      } else if (strcmp("verbose", arg) == 0) {
        if (params->verbose) return COMMAND_INVALID;
        params->verbose = BROTLI_TRUE;
      } else if (strcmp("version", arg) == 0) {
        /* Don't parse further. */
        return COMMAND_VERSION;
      } else {
        /* key=value */
        const char* value = strrchr(arg, '=');
        size_t key_len;
        if (!value || value[1] == 0) return COMMAND_INVALID;
        key_len = (size_t)(value - arg);
        value++;
        if (strncmp("lgwin", arg, key_len) == 0) {
          if (lgwin_set) return COMMAND_INVALID;
          lgwin_set = ParseInt(value, 0,
                               BROTLI_MAX_WINDOW_BITS, &params->lgwin);
          if (!lgwin_set) return COMMAND_INVALID;
          if (params->lgwin != 0 && params->lgwin < BROTLI_MIN_WINDOW_BITS) {
            return COMMAND_INVALID;
          }
        } else if (strncmp("output", arg, key_len) == 0) {
          if (output_set) return COMMAND_INVALID;
          params->output_path = value;
        } else if (strncmp("quality", arg, key_len) == 0) {
          if (quality_set) return COMMAND_INVALID;
          quality_set = ParseInt(value, BROTLI_MIN_QUALITY,
                                 BROTLI_MAX_QUALITY, &params->quality);
          if (!quality_set) return COMMAND_INVALID;
        } else if (strncmp("suffix", arg, key_len) == 0) {
          if (suffix_set) return COMMAND_INVALID;
          suffix_set = BROTLI_TRUE;
          params->suffix = value;
        } else {
          return COMMAND_INVALID;
        }
      }
    }
  }

  params->input_count = input_count;
  params->longest_path_len = longest_path_len;
  params->decompress = (command == COMMAND_DECOMPRESS);
  params->test_integrity = (command == COMMAND_TEST_INTEGRITY);

  if (input_count > 1 && output_set) return COMMAND_INVALID;
  if (params->test_integrity) {
    if (params->output_path) return COMMAND_INVALID;
    if (params->write_to_stdout) return COMMAND_INVALID;
  }
  if (strchr(params->suffix, '/') || strchr(params->suffix, '\\')) {
    return COMMAND_INVALID;
  }

  return command;
}