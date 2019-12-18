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
struct tpc_token {struct tpc_token* params; } ;
struct ctl_softc {int /*<<< orphan*/  tpc_lock; int /*<<< orphan*/  tpc_tokens; int /*<<< orphan*/  tpc_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CTL ; 
 struct tpc_token* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct tpc_token*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct tpc_token*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
ctl_tpc_shutdown(struct ctl_softc *softc)
{
	struct tpc_token *token;

	callout_drain(&softc->tpc_timeout);

	/* Free ROD tokens. */
	mtx_lock(&softc->tpc_lock);
	while ((token = TAILQ_FIRST(&softc->tpc_tokens)) != NULL) {
		TAILQ_REMOVE(&softc->tpc_tokens, token, links);
		free(token->params, M_CTL);
		free(token, M_CTL);
	}
	mtx_unlock(&softc->tpc_lock);
	mtx_destroy(&softc->tpc_lock);
}