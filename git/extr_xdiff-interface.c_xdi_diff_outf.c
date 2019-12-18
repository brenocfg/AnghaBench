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
typedef  int /*<<< orphan*/  xpparam_t ;
typedef  int /*<<< orphan*/  xdiff_emit_line_fn ;
typedef  scalar_t__ xdiff_emit_hunk_fn ;
typedef  int /*<<< orphan*/  xdemitconf_t ;
struct xdiff_emit_state {int /*<<< orphan*/  remainder; struct xdiff_emit_state* priv; int /*<<< orphan*/  out_line; int /*<<< orphan*/  out_hunk; void* consume_callback_data; int /*<<< orphan*/  line_fn; scalar_t__ hunk_fn; } ;
typedef  struct xdiff_emit_state xdemitcb_t ;
typedef  int /*<<< orphan*/  state ;
typedef  int /*<<< orphan*/  mmfile_t ;
typedef  int /*<<< orphan*/  ecb ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct xdiff_emit_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 
 int xdi_diff (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,struct xdiff_emit_state*) ; 
 int /*<<< orphan*/  xdiff_out_hunk ; 
 int /*<<< orphan*/  xdiff_outf ; 

int xdi_diff_outf(mmfile_t *mf1, mmfile_t *mf2,
		  xdiff_emit_hunk_fn hunk_fn,
		  xdiff_emit_line_fn line_fn,
		  void *consume_callback_data,
		  xpparam_t const *xpp, xdemitconf_t const *xecfg)
{
	int ret;
	struct xdiff_emit_state state;
	xdemitcb_t ecb;

	memset(&state, 0, sizeof(state));
	state.hunk_fn = hunk_fn;
	state.line_fn = line_fn;
	state.consume_callback_data = consume_callback_data;
	memset(&ecb, 0, sizeof(ecb));
	if (hunk_fn)
		ecb.out_hunk = xdiff_out_hunk;
	ecb.out_line = xdiff_outf;
	ecb.priv = &state;
	strbuf_init(&state.remainder, 0);
	ret = xdi_diff(mf1, mf2, xpp, xecfg, &ecb);
	strbuf_release(&state.remainder);
	return ret;
}