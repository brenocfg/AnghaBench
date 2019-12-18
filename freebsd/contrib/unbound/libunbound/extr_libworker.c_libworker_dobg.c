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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ub_ctx {int /*<<< orphan*/  rr_pipe; int /*<<< orphan*/  qq_pipe; } ;
struct libworker {int want_quit; struct ub_ctx* ctx; int /*<<< orphan*/  base; scalar_t__ is_bg_thread; int /*<<< orphan*/  thread_num; } ;
typedef  int /*<<< orphan*/  m ;

/* Variables and functions */
 int /*<<< orphan*/  UB_LIBCMD_QUIT ; 
 int /*<<< orphan*/  comm_base_dispatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libworker_delete (struct libworker*) ; 
 int /*<<< orphan*/  libworker_handle_control_cmd ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_thread_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tube_close_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tube_close_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tube_remove_bg_listen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tube_remove_bg_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tube_setup_bg_listen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct libworker*) ; 
 int /*<<< orphan*/  tube_setup_bg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tube_write_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void*
libworker_dobg(void* arg)
{
	/* setup */
	uint32_t m;
	struct libworker* w = (struct libworker*)arg;
	struct ub_ctx* ctx;
	if(!w) {
		log_err("libunbound bg worker init failed, nomem");
		return NULL;
	}
	ctx = w->ctx;
	log_thread_set(&w->thread_num);
#ifdef THREADS_DISABLED
	/* we are forked */
	w->is_bg_thread = 0;
	/* close non-used parts of the pipes */
	tube_close_write(ctx->qq_pipe);
	tube_close_read(ctx->rr_pipe);
#endif
	if(!tube_setup_bg_listen(ctx->qq_pipe, w->base, 
		libworker_handle_control_cmd, w)) {
		log_err("libunbound bg worker init failed, no bglisten");
		return NULL;
	}
	if(!tube_setup_bg_write(ctx->rr_pipe, w->base)) {
		log_err("libunbound bg worker init failed, no bgwrite");
		return NULL;
	}

	/* do the work */
	comm_base_dispatch(w->base);

	/* cleanup */
	m = UB_LIBCMD_QUIT;
	w->want_quit = 1;
	tube_remove_bg_listen(w->ctx->qq_pipe);
	tube_remove_bg_write(w->ctx->rr_pipe);
	libworker_delete(w);
	(void)tube_write_msg(ctx->rr_pipe, (uint8_t*)&m, 
		(uint32_t)sizeof(m), 0);
#ifdef THREADS_DISABLED
	/* close pipes from forked process before exit */
	tube_close_read(ctx->qq_pipe);
	tube_close_write(ctx->rr_pipe);
#endif
	return NULL;
}