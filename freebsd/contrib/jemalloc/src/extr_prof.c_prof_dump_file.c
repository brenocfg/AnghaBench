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
typedef  int /*<<< orphan*/  tsd_t ;
struct prof_tdata_merge_iter_arg_s {int /*<<< orphan*/  cnt_all; } ;
struct prof_gctx_merge_iter_arg_s {int dummy; } ;
struct prof_gctx_dump_iter_arg_s {int propagate_err; int /*<<< orphan*/  tsdn; } ;
typedef  int /*<<< orphan*/  prof_tdata_t ;
typedef  int /*<<< orphan*/  prof_gctx_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/ * gctx_tree_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ prof_dump_close (int) ; 
 int prof_dump_fd ; 
 scalar_t__ prof_dump_header (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ prof_dump_maps (int) ; 
 int prof_dump_open (int,char const*) ; 
 int /*<<< orphan*/  prof_gctx_dump_iter ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
prof_dump_file(tsd_t *tsd, bool propagate_err, const char *filename,
    bool leakcheck, prof_tdata_t *tdata,
    struct prof_tdata_merge_iter_arg_s *prof_tdata_merge_iter_arg,
    struct prof_gctx_merge_iter_arg_s *prof_gctx_merge_iter_arg,
    struct prof_gctx_dump_iter_arg_s *prof_gctx_dump_iter_arg,
    prof_gctx_tree_t *gctxs) {
	/* Create dump file. */
	if ((prof_dump_fd = prof_dump_open(propagate_err, filename)) == -1) {
		return true;
	}

	/* Dump profile header. */
	if (prof_dump_header(tsd_tsdn(tsd), propagate_err,
	    &prof_tdata_merge_iter_arg->cnt_all)) {
		goto label_write_error;
	}

	/* Dump per gctx profile stats. */
	prof_gctx_dump_iter_arg->tsdn = tsd_tsdn(tsd);
	prof_gctx_dump_iter_arg->propagate_err = propagate_err;
	if (gctx_tree_iter(gctxs, NULL, prof_gctx_dump_iter,
	    (void *)prof_gctx_dump_iter_arg) != NULL) {
		goto label_write_error;
	}

	/* Dump /proc/<pid>/maps if possible. */
	if (prof_dump_maps(propagate_err)) {
		goto label_write_error;
	}

	if (prof_dump_close(propagate_err)) {
		return true;
	}

	return false;
label_write_error:
	prof_dump_close(propagate_err);
	return true;
}