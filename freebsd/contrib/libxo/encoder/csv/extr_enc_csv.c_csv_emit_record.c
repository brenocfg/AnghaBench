#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xo_handle_t ;
typedef  int uint32_t ;
typedef  size_t ssize_t ;
struct TYPE_7__ {int f_flags; scalar_t__ f_value; scalar_t__ f_name; } ;
typedef  TYPE_1__ leaf_t ;
struct TYPE_8__ {size_t c_leaf_depth; int c_flags; int /*<<< orphan*/  c_value_buf; TYPE_1__* c_leaf; int /*<<< orphan*/  c_data; int /*<<< orphan*/  c_name_buf; } ;
typedef  TYPE_2__ csv_private_t ;

/* Variables and functions */
 int CF_HEADER_DONE ; 
 int CF_LEAFS_DONE ; 
 int CF_NO_HEADER ; 
 int LF_HAS_VALUE ; 
 int QF_NEEDS_ESCAPE ; 
 int QF_NEEDS_QUOTES ; 
 int XOF_FLUSH ; 
 int XOF_FLUSH_LINE ; 
 int /*<<< orphan*/  csv_append_newline (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  csv_dbg (int /*<<< orphan*/ *,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  csv_escape (int /*<<< orphan*/ *,char const*,int) ; 
 int csv_quote_flags (int /*<<< orphan*/ *,TYPE_2__*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  xo_buf_append (int /*<<< orphan*/ *,char const*,int) ; 
 char* xo_buf_data (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  xo_buf_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xo_flush_h (int /*<<< orphan*/ *) ; 
 int xo_get_flags (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
csv_emit_record (xo_handle_t *xop, csv_private_t *csv)
{
    csv_dbg(xop, csv, "csv: emit: ...\n");

    ssize_t fnum;
    uint32_t quote_flags;
    leaf_t *lp;

    /* If we have no data, then don't bother */
    if (csv->c_leaf_depth == 0)
	return;

    if (!(csv->c_flags & (CF_HEADER_DONE | CF_NO_HEADER))) {
	csv->c_flags |= CF_HEADER_DONE;

	for (fnum = 0; fnum < csv->c_leaf_depth; fnum++) {
	    lp = &csv->c_leaf[fnum];
	    const char *name = xo_buf_data(&csv->c_name_buf, lp->f_name);

	    if (fnum != 0)
		xo_buf_append(&csv->c_data, ",", 1);

	    xo_buf_append(&csv->c_data, name, strlen(name));
	}

	csv_append_newline(&csv->c_data, csv);
    }

    for (fnum = 0; fnum < csv->c_leaf_depth; fnum++) {
	lp = &csv->c_leaf[fnum];
	const char *value;

	if (lp->f_flags & LF_HAS_VALUE) {
	    value = xo_buf_data(&csv->c_value_buf, lp->f_value);
	} else {
	    value = "";
	}

	quote_flags = csv_quote_flags(xop, csv, value);

	if (fnum != 0)
	    xo_buf_append(&csv->c_data, ",", 1);

	if (quote_flags & QF_NEEDS_QUOTES)
	    xo_buf_append(&csv->c_data, "\"", 1);

	if (quote_flags & QF_NEEDS_ESCAPE)
	    csv_escape(&csv->c_data, value, strlen(value));
	else
	    xo_buf_append(&csv->c_data, value, strlen(value));

	if (quote_flags & QF_NEEDS_QUOTES)
	    xo_buf_append(&csv->c_data, "\"", 1);
    }

    csv_append_newline(&csv->c_data, csv);

    /* We flush if either flush flag is set */
    if (xo_get_flags(xop) & (XOF_FLUSH | XOF_FLUSH_LINE))
	xo_flush_h(xop);

    /* Clean out values from leafs */
    for (fnum = 0; fnum < csv->c_leaf_depth; fnum++) {
	lp = &csv->c_leaf[fnum];

	lp->f_flags &= ~LF_HAS_VALUE;
	lp->f_value = 0;
    }

    xo_buf_reset(&csv->c_value_buf);

    /*
     * Once we emit the first line, our set of leafs is locked and
     * cannot be changed.
     */
    csv->c_flags |= CF_LEAFS_DONE;
}