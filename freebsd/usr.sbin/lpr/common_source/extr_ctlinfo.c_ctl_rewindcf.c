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
struct TYPE_2__ {struct cjprivate* cji_priv; } ;
struct cjprivate {int /*<<< orphan*/  cji_fstream; TYPE_1__ pub; } ;
struct cjobinfo {struct cjprivate* cji_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,void*,void*) ; 

void
ctl_rewindcf(struct cjobinfo *cjinf)
{
	struct cjprivate *cpriv;

	if (cjinf == NULL)
		return;
	cpriv = cjinf->cji_priv;
	if ((cpriv == NULL) || (cpriv != cpriv->pub.cji_priv)) {
		syslog(LOG_ERR, "in ctl_rewindcf(%p): invalid cjinf (cpriv %p)",
		    (void *)cjinf, (void *)cpriv);
		return;
	}
	
	rewind(cpriv->cji_fstream);		/* assume no errors... :-) */
}