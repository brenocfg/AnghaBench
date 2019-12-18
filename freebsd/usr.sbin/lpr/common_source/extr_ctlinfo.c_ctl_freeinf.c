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
struct TYPE_2__ {int /*<<< orphan*/  cji_headruser; int /*<<< orphan*/  cji_mailto; int /*<<< orphan*/  cji_jobname; int /*<<< orphan*/  cji_curqueue; int /*<<< orphan*/  cji_class; int /*<<< orphan*/  cji_acctuser; int /*<<< orphan*/  cji_accthost; struct cjprivate* cji_priv; } ;
struct cjprivate {int /*<<< orphan*/ * cji_fstream; TYPE_1__ pub; } ;
struct cjobinfo {struct cjprivate* cji_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREESTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct cjprivate*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,void*,void*) ; 

void
ctl_freeinf(struct cjobinfo *cjinf)
{
#define FREESTR(xStr) \
	if (xStr != NULL) { \
		free(xStr); \
		xStr = NULL;\
	}

	struct cjprivate *cpriv;

	if (cjinf == NULL)
		return;
	cpriv = cjinf->cji_priv;
	if ((cpriv == NULL) || (cpriv != cpriv->pub.cji_priv)) {
		syslog(LOG_ERR, "in ctl_freeinf(%p): invalid cjinf (cpriv %p)",
		    (void *)cjinf, (void *)cpriv);
		return;
	}

	FREESTR(cpriv->pub.cji_accthost);
	FREESTR(cpriv->pub.cji_acctuser);
	FREESTR(cpriv->pub.cji_class);
	FREESTR(cpriv->pub.cji_curqueue);
	/* [cpriv->pub.cji_fname is part of cpriv-malloced area] */
	FREESTR(cpriv->pub.cji_jobname);
	FREESTR(cpriv->pub.cji_mailto);
	FREESTR(cpriv->pub.cji_headruser);

	if (cpriv->cji_fstream != NULL) {
		fclose(cpriv->cji_fstream);
		cpriv->cji_fstream = NULL;
	}

	cjinf->cji_priv = NULL;
	free(cpriv);
#undef FREESTR
}