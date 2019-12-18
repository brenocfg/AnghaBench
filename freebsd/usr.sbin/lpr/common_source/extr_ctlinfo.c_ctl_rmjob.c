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
struct cjobinfo {int dummy; } ;
typedef  int /*<<< orphan*/  errm ;

/* Variables and functions */
 int CTI_LINEMAX ; 
 int /*<<< orphan*/  ctl_freeinf (struct cjobinfo*) ; 
 char* ctl_getline (struct cjobinfo*) ; 
 struct cjobinfo* ctl_readcf (char const*,char const*) ; 
 int /*<<< orphan*/  ctl_rewindcf (struct cjobinfo*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 char* strdup (char*) ; 

char *
ctl_rmjob(const char *ptrname, const char *cfname)
{
	struct cjobinfo	*cjinf;
	char *lbuff;
	char errm[CTI_LINEMAX];

	cjinf = ctl_readcf(ptrname, cfname);
	if (cjinf == NULL) {
		snprintf(errm, sizeof(errm),
		    "ctl_renametf error cti_readcf(%s)", cfname);
		return strdup(errm);
	}

	ctl_rewindcf(cjinf);
	lbuff = ctl_getline(cjinf);
	while (lbuff != NULL) {
		/* obviously we need to fill in the following... */
		switch (lbuff[0]) {
		case 'S':
			break;
		case 'U':
			break;
		default:
			break;
		}
		lbuff = ctl_getline(cjinf);
	}

	ctl_freeinf(cjinf);
	cjinf = NULL;

	return NULL;
}