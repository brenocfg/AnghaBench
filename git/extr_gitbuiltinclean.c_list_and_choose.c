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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct menu_stuff {int nr; } ;
struct menu_opts {int flags; scalar_t__ prompt; scalar_t__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (int*,int) ; 
 int /*<<< orphan*/  CLEAN_COLOR_HEADER ; 
 int /*<<< orphan*/  CLEAN_COLOR_PROMPT ; 
 int /*<<< orphan*/  CLEAN_COLOR_RESET ; 
 int EOF ; 
 int MENU_OPTS_IMMEDIATE ; 
 int MENU_OPTS_LIST_ONLY ; 
 int MENU_OPTS_SINGLETON ; 
 struct strbuf STRBUF_INIT ; 
 char* _ (scalar_t__) ; 
 char* clean_get_color (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int*) ; 
 int parse_choice (struct menu_stuff*,int,struct strbuf,int**) ; 
 int /*<<< orphan*/  print_highlight_menu_stuff (struct menu_stuff*,int**) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  printf_ln (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  prompt_help_cmd (int) ; 
 int /*<<< orphan*/  st_add (int,int) ; 
 int /*<<< orphan*/  stdin ; 
 int strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_trim (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int* xcalloc (int /*<<< orphan*/ ,int) ; 
 int* xmalloc (int) ; 

__attribute__((used)) static int *list_and_choose(struct menu_opts *opts, struct menu_stuff *stuff)
{
	struct strbuf choice = STRBUF_INIT;
	int *chosen, *result;
	int nr = 0;
	int eof = 0;
	int i;

	ALLOC_ARRAY(chosen, stuff->nr);
	/* set chosen as uninitialized */
	for (i = 0; i < stuff->nr; i++)
		chosen[i] = -1;

	for (;;) {
		if (opts->header) {
			printf_ln("%s%s%s",
				  clean_get_color(CLEAN_COLOR_HEADER),
				  _(opts->header),
				  clean_get_color(CLEAN_COLOR_RESET));
		}

		/* chosen will be initialized by print_highlight_menu_stuff */
		print_highlight_menu_stuff(stuff, &chosen);

		if (opts->flags & MENU_OPTS_LIST_ONLY)
			break;

		if (opts->prompt) {
			printf("%s%s%s%s",
			       clean_get_color(CLEAN_COLOR_PROMPT),
			       _(opts->prompt),
			       opts->flags & MENU_OPTS_SINGLETON ? "> " : ">> ",
			       clean_get_color(CLEAN_COLOR_RESET));
		}

		if (strbuf_getline_lf(&choice, stdin) != EOF) {
			strbuf_trim(&choice);
		} else {
			eof = 1;
			break;
		}

		/* help for prompt */
		if (!strcmp(choice.buf, "?")) {
			prompt_help_cmd(opts->flags & MENU_OPTS_SINGLETON);
			continue;
		}

		/* for a multiple-choice menu, press ENTER (empty) will return back */
		if (!(opts->flags & MENU_OPTS_SINGLETON) && !choice.len)
			break;

		nr = parse_choice(stuff,
				  opts->flags & MENU_OPTS_SINGLETON,
				  choice,
				  &chosen);

		if (opts->flags & MENU_OPTS_SINGLETON) {
			if (nr)
				break;
		} else if (opts->flags & MENU_OPTS_IMMEDIATE) {
			break;
		}
	}

	if (eof) {
		result = xmalloc(sizeof(int));
		*result = EOF;
	} else {
		int j = 0;

		/*
		 * recalculate nr, if return back from menu directly with
		 * default selections.
		 */
		if (!nr) {
			for (i = 0; i < stuff->nr; i++)
				nr += chosen[i];
		}

		result = xcalloc(st_add(nr, 1), sizeof(int));
		for (i = 0; i < stuff->nr && j < nr; i++) {
			if (chosen[i])
				result[j++] = i;
		}
		result[j] = EOF;
	}

	free(chosen);
	strbuf_release(&choice);
	return result;
}