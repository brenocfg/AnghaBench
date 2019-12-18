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
struct TYPE_4__ {char* buf; size_t buf_valid_len; scalar_t__ curr_file; scalar_t__ nfiles; int /*<<< orphan*/ * current_input; int /*<<< orphan*/ * parser; scalar_t__ current_line; int /*<<< orphan*/  failures; int /*<<< orphan*/  err_cb_data; int /*<<< orphan*/  (* err_cb ) (int /*<<< orphan*/ ,char const*) ;void* current_filename; } ;
typedef  TYPE_1__ jq_util_input_state ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  jv_free (void*) ; 
 void* jv_invalid () ; 
 void* jv_string (char const*) ; 
 char* memchr (char*,char,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 char* next_file (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* strerror (scalar_t__) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int jq_util_input_read_more(jq_util_input_state *state) {
  if (!state->current_input || feof(state->current_input) || ferror(state->current_input)) {
    if (state->current_input && ferror(state->current_input)) {
      // System-level input error on the stream. It will be closed (below).
      // TODO: report it. Can't use 'state->err_cb()' as it is hard-coded for
      //       'open' related problems.
      fprintf(stderr,"jq: error: %s\n", strerror(errno));
    }
    if (state->current_input) {
      if (state->current_input == stdin) {
        clearerr(stdin); // perhaps we can read again; anyways, we don't fclose(stdin)
      } else {
        fclose(state->current_input);
      }
      state->current_input = NULL;
      jv_free(state->current_filename);
      state->current_filename = jv_invalid();
      state->current_line = 0 ;
    }
    const char *f = next_file(state);
    if (f != NULL) {
      if (!strcmp(f, "-")) {
        state->current_input = stdin;
        state->current_filename = jv_string("<stdin>");
      } else {
        state->current_input = fopen(f, "r");
        state->current_filename = jv_string(f);
        if (!state->current_input) {
          state->err_cb(state->err_cb_data, f);
          state->failures++;
        }
      }
      state->current_line = 0;
    }
  }

  state->buf[0] = 0;
  state->buf_valid_len = 0;
  if (state->current_input) {
    char *res;
    memset(state->buf, 0xff, sizeof(state->buf));

    while (!(res = fgets(state->buf, sizeof(state->buf), state->current_input)) &&
           ferror(state->current_input) && errno == EINTR)
      clearerr(state->current_input);
    if (res == NULL) {
      state->buf[0] = 0;
      if (ferror(state->current_input))
        state->failures++;
    } else {
      const char *p = memchr(state->buf, '\n', sizeof(state->buf));

      if (p != NULL)
        state->current_line++;

      if (p == NULL && state->parser != NULL) {
        /*
         * There should be no NULs in JSON texts (but JSON text
         * sequences are another story).
         */
        state->buf_valid_len = strlen(state->buf);
      } else if (p == NULL && feof(state->current_input)) {
        size_t i;

        /*
         * XXX We don't know how many bytes we've read!
         *
         * We can't use getline() because there need not be any newlines
         * in the input.  The only entirely correct choices are: use
         * fgetc() or fread().  Using fread() will complicate buffer
         * management here.
         *
         * For now we check how much fgets() read by scanning backwards for the
         * terminating '\0'. This only works because we previously memset our
         * buffer with something nonzero.
         */
        for (p = state->buf, i = sizeof(state->buf) - 1; i > 0; i--) {
          if (state->buf[i] == '\0')
            break;
        }
        state->buf_valid_len = i;
      } else if (p == NULL) {
        state->buf_valid_len = sizeof(state->buf) - 1;
      } else {
        state->buf_valid_len = (p - state->buf) + 1;
      }
    }
  }
  return state->curr_file == state->nfiles &&
      (!state->current_input || feof(state->current_input) || ferror(state->current_input));
}