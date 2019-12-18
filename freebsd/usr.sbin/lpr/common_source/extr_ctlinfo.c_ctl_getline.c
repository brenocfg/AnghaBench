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
struct TYPE_2__ {char* cji_fname; int /*<<< orphan*/  cji_curqueue; struct cjprivate* cji_priv; } ;
struct cjprivate {char* cji_buff; TYPE_1__ pub; int /*<<< orphan*/  cji_dumpit; int /*<<< orphan*/  cji_fstream; int /*<<< orphan*/  cji_buffsize; } ;
struct cjobinfo {struct cjprivate* cji_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/ * ctl_dbgfile ; 
 scalar_t__ errno ; 
 char* fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,int,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,void*,char*,...) ; 

__attribute__((used)) static char *
ctl_getline(struct cjobinfo *cjinf)
{
	char *strp, *nl;
	struct cjprivate *cpriv;

	if (cjinf == NULL)
		return NULL;
	cpriv = cjinf->cji_priv;
	if ((cpriv == NULL) || (cpriv != cpriv->pub.cji_priv)) {
		syslog(LOG_ERR, "in ctl_getline(%p): invalid cjinf (cpriv %p)",
		    (void *)cjinf, (void *)cpriv);
		return NULL;
	}

	errno = 0;
	strp = fgets(cpriv->cji_buff, cpriv->cji_buffsize, cpriv->cji_fstream);
	if (strp == NULL) {
		if (errno != 0)
			syslog(LOG_ERR, "%s: ctl_getline error fgets(%s): %s",
			    cpriv->pub.cji_curqueue, cpriv->pub.cji_fname,
			    strerror(errno));
		return NULL;
	}
	nl = strchr(strp, '\n');
	if (nl != NULL)
		*nl = '\0';

#ifdef DEBUGREADCF_FNAME
	/* I'd like to find out if the previous work to expand tabs was ever
	 * really used, and if so, on what lines and for what reason.
	 * Yes, all this work probably means I'm obsessed about this 'tab'
	 * issue, but isn't programming a matter of obsession?
	 */
	{
		int tabcnt;
		char *ch;

		tabcnt = 0;
		ch = strp;
		for (ch = strp; *ch != '\0'; ch++) {
			if (*ch == '\t')
				tabcnt++;
		}

		if (tabcnt && (ctl_dbgfile != NULL)) {
			cpriv->cji_dumpit++;
			fprintf(ctl_dbgfile, "%s: tabs=%d '%s'\n",
			    cpriv->pub.cji_fname, tabcnt, cpriv->cji_buff);
		}
	}
#endif
	return strp;
}