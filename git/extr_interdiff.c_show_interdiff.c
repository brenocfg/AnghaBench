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
struct strbuf {int dummy; } ;
struct rev_info {int /*<<< orphan*/  idiff_oid2; int /*<<< orphan*/  idiff_oid1; int /*<<< orphan*/  diffopt; } ;
struct diff_options {struct strbuf* output_prefix_data; int /*<<< orphan*/  output_prefix; int /*<<< orphan*/  output_format; } ;
typedef  int /*<<< orphan*/  opts ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_FORMAT_PATCH ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  diff_flush (struct diff_options*) ; 
 int /*<<< orphan*/  diff_setup_done (struct diff_options*) ; 
 int /*<<< orphan*/  diff_tree_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct diff_options*) ; 
 int /*<<< orphan*/  diffcore_std (struct diff_options*) ; 
 int /*<<< orphan*/  idiff_prefix_cb ; 
 int /*<<< orphan*/  memcpy (struct diff_options*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strbuf_addchars (struct strbuf*,char,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

void show_interdiff(struct rev_info *rev, int indent)
{
	struct diff_options opts;
	struct strbuf prefix = STRBUF_INIT;

	memcpy(&opts, &rev->diffopt, sizeof(opts));
	opts.output_format = DIFF_FORMAT_PATCH;
	opts.output_prefix = idiff_prefix_cb;
	strbuf_addchars(&prefix, ' ', indent);
	opts.output_prefix_data = &prefix;
	diff_setup_done(&opts);

	diff_tree_oid(rev->idiff_oid1, rev->idiff_oid2, "", &opts);
	diffcore_std(&opts);
	diff_flush(&opts);

	strbuf_release(&prefix);
}