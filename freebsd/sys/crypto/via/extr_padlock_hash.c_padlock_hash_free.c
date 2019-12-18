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
struct padlock_session {int /*<<< orphan*/ * ses_octx; TYPE_1__* ses_axf; int /*<<< orphan*/ * ses_ictx; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctxsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PADLOCK ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padlock_free_ctx (TYPE_1__*,int /*<<< orphan*/ *) ; 

void
padlock_hash_free(struct padlock_session *ses)
{

	if (ses->ses_ictx != NULL) {
		padlock_free_ctx(ses->ses_axf, ses->ses_ictx);
		bzero(ses->ses_ictx, ses->ses_axf->ctxsize);
		free(ses->ses_ictx, M_PADLOCK);
		ses->ses_ictx = NULL;
	}
	if (ses->ses_octx != NULL) {
		padlock_free_ctx(ses->ses_axf, ses->ses_octx);
		bzero(ses->ses_octx, ses->ses_axf->ctxsize);
		free(ses->ses_octx, M_PADLOCK);
		ses->ses_octx = NULL;
	}
}