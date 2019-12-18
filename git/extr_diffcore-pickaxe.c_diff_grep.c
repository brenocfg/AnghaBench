#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  interhunkctxlen; int /*<<< orphan*/  ctxlen; } ;
typedef  TYPE_1__ xpparam_t ;
typedef  int /*<<< orphan*/  xpp ;
typedef  int /*<<< orphan*/  xecfg ;
typedef  TYPE_1__ xdemitconf_t ;
struct diffgrep_cb {int hit; int /*<<< orphan*/ * regexp; } ;
struct diff_options {int /*<<< orphan*/  interhunkcontext; int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  regmatch_t ;
typedef  int /*<<< orphan*/  regex_t ;
struct TYPE_12__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ mmfile_t ;
typedef  int /*<<< orphan*/  kwset_t ;

/* Variables and functions */
 int /*<<< orphan*/  diffgrep_consume ; 
 int /*<<< orphan*/  discard_hunk_line ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regexec_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xdi_diff_outf (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct diffgrep_cb*,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int diff_grep(mmfile_t *one, mmfile_t *two,
		     struct diff_options *o,
		     regex_t *regexp, kwset_t kws)
{
	regmatch_t regmatch;
	struct diffgrep_cb ecbdata;
	xpparam_t xpp;
	xdemitconf_t xecfg;

	if (!one)
		return !regexec_buf(regexp, two->ptr, two->size,
				    1, &regmatch, 0);
	if (!two)
		return !regexec_buf(regexp, one->ptr, one->size,
				    1, &regmatch, 0);

	/*
	 * We have both sides; need to run textual diff and see if
	 * the pattern appears on added/deleted lines.
	 */
	memset(&xpp, 0, sizeof(xpp));
	memset(&xecfg, 0, sizeof(xecfg));
	ecbdata.regexp = regexp;
	ecbdata.hit = 0;
	xecfg.ctxlen = o->context;
	xecfg.interhunkctxlen = o->interhunkcontext;
	if (xdi_diff_outf(one, two, discard_hunk_line, diffgrep_consume,
			  &ecbdata, &xpp, &xecfg))
		return 0;
	return ecbdata.hit;
}