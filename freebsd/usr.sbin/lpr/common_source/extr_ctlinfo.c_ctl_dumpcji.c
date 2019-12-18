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
struct TYPE_2__ {int /*<<< orphan*/ * cji_priv; int /*<<< orphan*/  cji_headruser; int /*<<< orphan*/  cji_mailto; int /*<<< orphan*/  cji_jobname; int /*<<< orphan*/  cji_fname; int /*<<< orphan*/  cji_curqueue; int /*<<< orphan*/  cji_class; int /*<<< orphan*/  cji_acctuser; int /*<<< orphan*/  cji_accthost; } ;
struct cjprivate {TYPE_1__ pub; int /*<<< orphan*/  cji_buff; } ;
struct cjobinfo {struct cjprivate* cji_priv; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  PRINTSTR (char*,int /*<<< orphan*/ ) ; 
 int ctl_dbgline ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void
ctl_dumpcji(FILE *dbg_stream, const char *heading, struct cjobinfo *cjinf)
{
#define PRINTSTR(xHdr,xStr) \
	astr = xStr; \
	ctl_dbgline++; \
	fprintf(dbg_stream, "%4d] %12s = ", ctl_dbgline, xHdr); \
	if (astr == NULL) \
		fprintf(dbg_stream, "NULL\n"); \
	else \
		fprintf(dbg_stream, "%p -> %s\n", astr, astr)

	struct cjprivate *cpriv;
	char *astr;

	if (cjinf == NULL) {
		fprintf(dbg_stream,
		    "ctl_dumpcji: ptr to cjobinfo for '%s' is NULL\n",
		    heading);
		return;
	}
	cpriv = cjinf->cji_priv;

	fprintf(dbg_stream, "ctl_dumpcji: Dump '%s' of cjobinfo at %p->%p\n",
	    heading, (void *)cjinf, cpriv->cji_buff);

	PRINTSTR("accthost.H", cpriv->pub.cji_accthost);
	PRINTSTR("acctuser.P", cpriv->pub.cji_acctuser);
	PRINTSTR("class.C", cpriv->pub.cji_class);
	PRINTSTR("cf-qname", cpriv->pub.cji_curqueue);
	PRINTSTR("cf-fname", cpriv->pub.cji_fname);
	PRINTSTR("jobname.J", cpriv->pub.cji_jobname);
	PRINTSTR("mailto.M", cpriv->pub.cji_mailto);
	PRINTSTR("headruser.L", cpriv->pub.cji_headruser);

	ctl_dbgline++;
	fprintf(dbg_stream, "%4d] %12s = ", ctl_dbgline, "*cjprivate");
	if (cpriv->pub.cji_priv == NULL)
		fprintf(dbg_stream, "NULL !!\n");
	else
		fprintf(dbg_stream, "%p\n", (void *)cpriv->pub.cji_priv);

	fprintf(dbg_stream, "|- - - - --> Dump '%s' complete\n", heading);

	/* flush output for the benefit of anyone doing a 'tail -f' */
	fflush(dbg_stream);

#undef PRINTSTR
}