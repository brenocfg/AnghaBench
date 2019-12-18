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
struct glxsb_session {int /*<<< orphan*/ * ses_octx; TYPE_1__* ses_axf; int /*<<< orphan*/ * ses_ictx; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctxsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_GLXSB ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
glxsb_hash_free(struct glxsb_session *ses)
{

	if (ses->ses_ictx != NULL) {
		bzero(ses->ses_ictx, ses->ses_axf->ctxsize);
		free(ses->ses_ictx, M_GLXSB);
		ses->ses_ictx = NULL;
	}
	if (ses->ses_octx != NULL) {
		bzero(ses->ses_octx, ses->ses_axf->ctxsize);
		free(ses->ses_octx, M_GLXSB);
		ses->ses_octx = NULL;
	}
}