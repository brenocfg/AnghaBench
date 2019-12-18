#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct combine_diff_state {long flags; unsigned long nmask; int lno; int num_parent; int n; struct sline* sline; } ;
typedef  struct combine_diff_state xpparam_t ;
typedef  int /*<<< orphan*/  xpp ;
typedef  int /*<<< orphan*/  xecfg ;
typedef  struct combine_diff_state xdemitconf_t ;
struct userdiff_driver {int dummy; } ;
struct TYPE_6__ {scalar_t__ len; int /*<<< orphan*/ * lost_tail; scalar_t__ lost_head; } ;
struct sline {unsigned int* p_lno; unsigned long flag; struct lline* lost; TYPE_1__ plost; int /*<<< orphan*/  lenlost; } ;
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct lline {unsigned long parent_map; struct lline* next; } ;
typedef  int /*<<< orphan*/  state ;
struct TYPE_7__ {unsigned long size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ mmfile_t ;

/* Variables and functions */
 struct lline* coalesce_lines (struct lline*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int,long) ; 
 int /*<<< orphan*/  consume_hunk ; 
 int /*<<< orphan*/  consume_line ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grab_blob (struct repository*,struct object_id const*,unsigned int,unsigned long*,struct userdiff_driver*,char const*) ; 
 int /*<<< orphan*/  memset (struct combine_diff_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 scalar_t__ xdi_diff_outf (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct combine_diff_state*,struct combine_diff_state*,struct combine_diff_state*) ; 

__attribute__((used)) static void combine_diff(struct repository *r,
			 const struct object_id *parent, unsigned int mode,
			 mmfile_t *result_file,
			 struct sline *sline, unsigned int cnt, int n,
			 int num_parent, int result_deleted,
			 struct userdiff_driver *textconv,
			 const char *path, long flags)
{
	unsigned int p_lno, lno;
	unsigned long nmask = (1UL << n);
	xpparam_t xpp;
	xdemitconf_t xecfg;
	mmfile_t parent_file;
	struct combine_diff_state state;
	unsigned long sz;

	if (result_deleted)
		return; /* result deleted */

	parent_file.ptr = grab_blob(r, parent, mode, &sz, textconv, path);
	parent_file.size = sz;
	memset(&xpp, 0, sizeof(xpp));
	xpp.flags = flags;
	memset(&xecfg, 0, sizeof(xecfg));
	memset(&state, 0, sizeof(state));
	state.nmask = nmask;
	state.sline = sline;
	state.lno = 1;
	state.num_parent = num_parent;
	state.n = n;

	if (xdi_diff_outf(&parent_file, result_file, consume_hunk,
			  consume_line, &state, &xpp, &xecfg))
		die("unable to generate combined diff for %s",
		    oid_to_hex(parent));
	free(parent_file.ptr);

	/* Assign line numbers for this parent.
	 *
	 * sline[lno].p_lno[n] records the first line number
	 * (counting from 1) for parent N if the final hunk display
	 * started by showing sline[lno] (possibly showing the lost
	 * lines attached to it first).
	 */
	for (lno = 0,  p_lno = 1; lno <= cnt; lno++) {
		struct lline *ll;
		sline[lno].p_lno[n] = p_lno;

		/* Coalesce new lines */
		if (sline[lno].plost.lost_head) {
			struct sline *sl = &sline[lno];
			sl->lost = coalesce_lines(sl->lost, &sl->lenlost,
						  sl->plost.lost_head,
						  sl->plost.len, n, flags);
			sl->plost.lost_head = sl->plost.lost_tail = NULL;
			sl->plost.len = 0;
		}

		/* How many lines would this sline advance the p_lno? */
		ll = sline[lno].lost;
		while (ll) {
			if (ll->parent_map & nmask)
				p_lno++; /* '-' means parent had it */
			ll = ll->next;
		}
		if (lno < cnt && !(sline[lno].flag & nmask))
			p_lno++; /* no '+' means parent had it */
	}
	sline[lno].p_lno[n] = p_lno; /* trailer */
}