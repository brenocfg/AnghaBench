#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct libworker {int /*<<< orphan*/  back; int /*<<< orphan*/  sslctx; TYPE_1__* env; scalar_t__ is_bg_thread; int /*<<< orphan*/  is_bg; int /*<<< orphan*/  ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  rnd; int /*<<< orphan*/  hints; int /*<<< orphan*/  fwds; int /*<<< orphan*/  scratch; int /*<<< orphan*/  scratch_buffer; int /*<<< orphan*/  alloc; int /*<<< orphan*/  mesh; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_release_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  forwards_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hints_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mesh_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outside_network_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outside_network_quit_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regional_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ub_randfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
libworker_delete_env(struct libworker* w)
{
	if(w->env) {
		outside_network_quit_prepare(w->back);
		mesh_delete(w->env->mesh);
		context_release_alloc(w->ctx, w->env->alloc, 
			!w->is_bg || w->is_bg_thread);
		sldns_buffer_free(w->env->scratch_buffer);
		regional_destroy(w->env->scratch);
		forwards_delete(w->env->fwds);
		hints_delete(w->env->hints);
		ub_randfree(w->env->rnd);
		free(w->env);
	}
#ifdef HAVE_SSL
	SSL_CTX_free(w->sslctx);
#endif
	outside_network_delete(w->back);
}