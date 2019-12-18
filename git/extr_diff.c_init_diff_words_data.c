#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct emitted_diff_symbols {int dummy; } ;
struct emit_callback {TYPE_2__* diff_words; } ;
struct TYPE_10__ {void* color; } ;
struct TYPE_9__ {void* color; } ;
struct TYPE_8__ {void* color; } ;
struct diff_words_style {scalar_t__ type; TYPE_5__ ctx; TYPE_4__ new_word; TYPE_3__ old_word; } ;
struct diff_words_data {int dummy; } ;
struct diff_options {scalar_t__ word_diff; int /*<<< orphan*/  use_color; void* word_regex; TYPE_1__* repo; void* emitted_symbols; } ;
struct diff_filespec {int dummy; } ;
typedef  int /*<<< orphan*/  regex_t ;
struct TYPE_7__ {scalar_t__ type; struct diff_words_style* style; int /*<<< orphan*/ * word_regex; struct diff_options* opt; } ;
struct TYPE_6__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct diff_words_style*) ; 
 int /*<<< orphan*/  DIFF_CONTEXT ; 
 int /*<<< orphan*/  DIFF_FILE_NEW ; 
 int /*<<< orphan*/  DIFF_FILE_OLD ; 
 int REG_EXTENDED ; 
 int REG_NEWLINE ; 
 int /*<<< orphan*/  die (char*,void*) ; 
 void* diff_get_color_opt (struct diff_options*,int /*<<< orphan*/ ) ; 
 void* diff_word_regex_cfg ; 
 struct diff_words_style* diff_words_styles ; 
 int /*<<< orphan*/  memcpy (struct diff_options*,struct diff_options*,int) ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,void*,int) ; 
 void* userdiff_word_regex (struct diff_filespec*,int /*<<< orphan*/ ) ; 
 scalar_t__ want_color (int /*<<< orphan*/ ) ; 
 void* xcalloc (int,int) ; 
 struct diff_options* xmalloc (int) ; 

__attribute__((used)) static void init_diff_words_data(struct emit_callback *ecbdata,
				 struct diff_options *orig_opts,
				 struct diff_filespec *one,
				 struct diff_filespec *two)
{
	int i;
	struct diff_options *o = xmalloc(sizeof(struct diff_options));
	memcpy(o, orig_opts, sizeof(struct diff_options));

	ecbdata->diff_words =
		xcalloc(1, sizeof(struct diff_words_data));
	ecbdata->diff_words->type = o->word_diff;
	ecbdata->diff_words->opt = o;

	if (orig_opts->emitted_symbols)
		o->emitted_symbols =
			xcalloc(1, sizeof(struct emitted_diff_symbols));

	if (!o->word_regex)
		o->word_regex = userdiff_word_regex(one, o->repo->index);
	if (!o->word_regex)
		o->word_regex = userdiff_word_regex(two, o->repo->index);
	if (!o->word_regex)
		o->word_regex = diff_word_regex_cfg;
	if (o->word_regex) {
		ecbdata->diff_words->word_regex = (regex_t *)
			xmalloc(sizeof(regex_t));
		if (regcomp(ecbdata->diff_words->word_regex,
			    o->word_regex,
			    REG_EXTENDED | REG_NEWLINE))
			die("invalid regular expression: %s",
			    o->word_regex);
	}
	for (i = 0; i < ARRAY_SIZE(diff_words_styles); i++) {
		if (o->word_diff == diff_words_styles[i].type) {
			ecbdata->diff_words->style =
				&diff_words_styles[i];
			break;
		}
	}
	if (want_color(o->use_color)) {
		struct diff_words_style *st = ecbdata->diff_words->style;
		st->old_word.color = diff_get_color_opt(o, DIFF_FILE_OLD);
		st->new_word.color = diff_get_color_opt(o, DIFF_FILE_NEW);
		st->ctx.color = diff_get_color_opt(o, DIFF_CONTEXT);
	}
}