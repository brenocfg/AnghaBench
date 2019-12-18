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
struct printer {char* acct_file; char* form_feed; char* log_file; char* lock_file; char* lp; char* mode_set; char* restrict_grp; char* remote_host; char* remote_queue; char* spool_dir; char* stat_recv; char* stat_send; char* status_file; char* trailer; int tof; int rp_matches_local; char** filters; void* rw; void* header_last; void* no_header; void* no_formfeed; void* no_copies; void* short_banner; void* restricted; void* resend_copies; int /*<<< orphan*/  page_plength; int /*<<< orphan*/  page_pwidth; int /*<<< orphan*/  page_width; int /*<<< orphan*/  page_length; int /*<<< orphan*/  price100; int /*<<< orphan*/  max_blocks; int /*<<< orphan*/  max_copies; int /*<<< orphan*/  daemon_user; int /*<<< orphan*/  conn_timeout; int /*<<< orphan*/  baud_rate; int /*<<< orphan*/ * printer; } ;
typedef  enum lpd_filters { ____Placeholder_lpd_filters } lpd_filters ;

/* Variables and functions */
 int /*<<< orphan*/  CHK (int) ; 
 int /*<<< orphan*/  DEFFF ; 
 int /*<<< orphan*/  DEFLENGTH ; 
 int /*<<< orphan*/  DEFLOCK ; 
 int /*<<< orphan*/  DEFLP ; 
 int /*<<< orphan*/  DEFMAXCOPIES ; 
 int /*<<< orphan*/  DEFMX ; 
 int /*<<< orphan*/  DEFSTAT ; 
 int /*<<< orphan*/  DEFTIMEOUT ; 
 int /*<<< orphan*/  DEFUID ; 
 int /*<<< orphan*/  DEFWIDTH ; 
 int LPF_COUNT ; 
 int PCAPERR_NOTFOUND ; 
 int PCAPERR_OSERR ; 
 int /*<<< orphan*/  _PATH_CONSOLE ; 
 int /*<<< orphan*/  _PATH_DEFDEVLP ; 
 int /*<<< orphan*/  _PATH_DEFSPOOL ; 
 int /*<<< orphan*/ * capdb_canonical_name (char*) ; 
 void* capdb_getaltlog (char*,char*,char*) ; 
 int capdb_getaltnum (char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int capdb_getaltstr (char*,char*,char*,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ cgetmatch (char*,char*) ; 
 char** filters ; 
 int /*<<< orphan*/  free (char*) ; 
 char** longfilters ; 

__attribute__((used)) static int
getprintcap_int(char *bp, struct printer *pp)
{
	enum lpd_filters filt;
	char *rp_name;
	int error;

	if ((pp->printer = capdb_canonical_name(bp)) == NULL)
		return PCAPERR_OSERR;

#define CHK(x) do {if ((x) == PCAPERR_OSERR) return PCAPERR_OSERR;}while(0)
	CHK(capdb_getaltstr(bp, "af", "acct.file", 0, &pp->acct_file));
	CHK(capdb_getaltnum(bp, "br", "tty.rate", 0, &pp->baud_rate));
	CHK(capdb_getaltnum(bp, "ct", "remote.timeout", DEFTIMEOUT, 
			    &pp->conn_timeout));
	CHK(capdb_getaltnum(bp, "du", "daemon.user", DEFUID, 
			    &pp->daemon_user));
	CHK(capdb_getaltstr(bp, "ff", "job.formfeed", DEFFF, &pp->form_feed));
	CHK(capdb_getaltstr(bp, "lf", "spool.log", _PATH_CONSOLE, 
			    &pp->log_file));
	CHK(capdb_getaltstr(bp, "lo", "spool.lock", DEFLOCK, &pp->lock_file));
	CHK(capdb_getaltstr(bp, "lp", "tty.device", _PATH_DEFDEVLP, &pp->lp));
	CHK(capdb_getaltnum(bp, "mc", "max.copies", DEFMAXCOPIES, 
			    &pp->max_copies));
	CHK(capdb_getaltstr(bp, "ms", "tty.mode", 0, &pp->mode_set));
	CHK(capdb_getaltnum(bp, "mx", "max.blocks", DEFMX, &pp->max_blocks));
	CHK(capdb_getaltnum(bp, "pc", "acct.price", 0, &pp->price100));
	CHK(capdb_getaltnum(bp, "pl", "page.length", DEFLENGTH,
			    &pp->page_length));
	CHK(capdb_getaltnum(bp, "pw", "page.width", DEFWIDTH, 
			    &pp->page_width));
	CHK(capdb_getaltnum(bp, "px", "page.pwidth", 0, &pp->page_pwidth));
	CHK(capdb_getaltnum(bp, "py", "page.plength", 0, &pp->page_plength));
	CHK(capdb_getaltstr(bp, "rg", "daemon.restrictgrp", 0, 
			    &pp->restrict_grp));
	CHK(capdb_getaltstr(bp, "rm", "remote.host", 0, &pp->remote_host));
	CHK(capdb_getaltstr(bp, "rp", "remote.queue", DEFLP, 
			    &pp->remote_queue));
	CHK(capdb_getaltstr(bp, "sd", "spool.dir", _PATH_DEFSPOOL,
			    &pp->spool_dir));
	CHK(capdb_getaltstr(bp, "sr", "stat.recv", 0, &pp->stat_recv));
	CHK(capdb_getaltstr(bp, "ss", "stat.send", 0, &pp->stat_send));
	CHK(capdb_getaltstr(bp, "st", "spool.status", DEFSTAT,
			    &pp->status_file));
	CHK(capdb_getaltstr(bp, "tr", "job.trailer", 0, &pp->trailer));

	pp->resend_copies = capdb_getaltlog(bp, "rc", "remote.resend_copies");
	pp->restricted = capdb_getaltlog(bp, "rs", "daemon.restricted");
	pp->short_banner = capdb_getaltlog(bp, "sb", "banner.short");
	pp->no_copies = capdb_getaltlog(bp, "sc", "job.no_copies");
	pp->no_formfeed = capdb_getaltlog(bp, "sf", "job.no_formfeed");
	pp->no_header = capdb_getaltlog(bp, "sh", "banner.disable");
	pp->header_last = capdb_getaltlog(bp, "hl", "banner.last");
	pp->rw = capdb_getaltlog(bp, "rw", "tty.rw");
	pp->tof = !capdb_getaltlog(bp, "fo", "job.topofform");
	
	/*
	 * Decide if the remote printer name matches the local printer name.
	 * If no name is given then we assume they mean them to match.
	 * If a name is given see if the rp_name is one of the names for
	 * this printer.
	 */
	pp->rp_matches_local = 1;
	CHK((error = capdb_getaltstr(bp, "rp", "remote.queue", 0, &rp_name)));
	if (error != PCAPERR_NOTFOUND && rp_name != NULL) {
		if (cgetmatch(bp,rp_name) != 0)
			pp->rp_matches_local = 0;
		free(rp_name);
	}

	/*
	 * Filters:
	 */
	for (filt = 0; filt < LPF_COUNT; filt++) {
		CHK(capdb_getaltstr(bp, filters[filt], longfilters[filt], 0,
				    &pp->filters[filt]));
	}

	return 0;
}