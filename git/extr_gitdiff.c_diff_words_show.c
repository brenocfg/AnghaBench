#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ ctxlen; scalar_t__ flags; } ;
typedef  TYPE_2__ xpparam_t ;
typedef  int /*<<< orphan*/  xpp ;
typedef  int /*<<< orphan*/  xecfg ;
typedef  TYPE_2__ xdemitconf_t ;
struct diff_words_style {int /*<<< orphan*/  newline; int /*<<< orphan*/  ctx; int /*<<< orphan*/  old_word; } ;
struct TYPE_13__ {scalar_t__ size; scalar_t__ ptr; } ;
struct TYPE_12__ {TYPE_1__ text; } ;
struct diff_words_data {scalar_t__ current_plus; TYPE_10__ plus; TYPE_10__ minus; struct diff_options* opt; int /*<<< orphan*/  word_regex; scalar_t__ last_minus; struct diff_words_style* style; } ;
struct diff_options {int dummy; } ;
struct TYPE_15__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_4__ mmfile_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_SYMBOL_WORD_DIFF ; 
 int /*<<< orphan*/  assert (struct diff_options*) ; 
 scalar_t__ color_words_output_graph_prefix (struct diff_words_data*) ; 
 int /*<<< orphan*/  die (char*) ; 
 char* diff_line_prefix (struct diff_options*) ; 
 int /*<<< orphan*/  diff_words_fill (TYPE_10__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_diff_symbol (struct diff_options*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fn_out_diff_words_aux ; 
 int /*<<< orphan*/  fn_out_diff_words_write_helper (struct diff_options*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ xdi_diff_outf (TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct diff_words_data*,TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static void diff_words_show(struct diff_words_data *diff_words)
{
	xpparam_t xpp;
	xdemitconf_t xecfg;
	mmfile_t minus, plus;
	struct diff_words_style *style = diff_words->style;

	struct diff_options *opt = diff_words->opt;
	const char *line_prefix;

	assert(opt);
	line_prefix = diff_line_prefix(opt);

	/* special case: only removal */
	if (!diff_words->plus.text.size) {
		emit_diff_symbol(diff_words->opt, DIFF_SYMBOL_WORD_DIFF,
				 line_prefix, strlen(line_prefix), 0);
		fn_out_diff_words_write_helper(diff_words->opt,
			&style->old_word, style->newline,
			diff_words->minus.text.size,
			diff_words->minus.text.ptr);
		diff_words->minus.text.size = 0;
		return;
	}

	diff_words->current_plus = diff_words->plus.text.ptr;
	diff_words->last_minus = 0;

	memset(&xpp, 0, sizeof(xpp));
	memset(&xecfg, 0, sizeof(xecfg));
	diff_words_fill(&diff_words->minus, &minus, diff_words->word_regex);
	diff_words_fill(&diff_words->plus, &plus, diff_words->word_regex);
	xpp.flags = 0;
	/* as only the hunk header will be parsed, we need a 0-context */
	xecfg.ctxlen = 0;
	if (xdi_diff_outf(&minus, &plus, fn_out_diff_words_aux, NULL,
			  diff_words, &xpp, &xecfg))
		die("unable to generate word diff");
	free(minus.ptr);
	free(plus.ptr);
	if (diff_words->current_plus != diff_words->plus.text.ptr +
			diff_words->plus.text.size) {
		if (color_words_output_graph_prefix(diff_words))
			emit_diff_symbol(diff_words->opt, DIFF_SYMBOL_WORD_DIFF,
					 line_prefix, strlen(line_prefix), 0);
		fn_out_diff_words_write_helper(diff_words->opt,
			&style->ctx, style->newline,
			diff_words->plus.text.ptr + diff_words->plus.text.size
			- diff_words->current_plus, diff_words->current_plus);
	}
	diff_words->minus.text.size = diff_words->plus.text.size = 0;
}