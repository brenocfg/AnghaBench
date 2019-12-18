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
typedef  int /*<<< orphan*/  xdrproc_t ;
struct ypxfr_mapname {char* xfrmap; char* xfrdomain; char* xfrmap_filename; int /*<<< orphan*/  xfr_db_type; } ;
struct xfr {int dummy; } ;
struct timeval {int member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  PERM_SECURE ; 
 scalar_t__ RPC_SUCCESS ; 
 int /*<<< orphan*/  XFR_DB_BSD_HASH ; 
 int /*<<< orphan*/  YPXFRD_FREEBSD_PROG ; 
 int /*<<< orphan*/  YPXFRD_FREEBSD_VERS ; 
 int /*<<< orphan*/  YPXFRD_GETMAP ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 scalar_t__ clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,struct timeval) ; 
 int /*<<< orphan*/ * clnt_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clnt_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clnt_sperror (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int fp ; 
 int open (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 scalar_t__ xdr_my_xfr ; 
 scalar_t__ xdr_ypxfr_mapname ; 
 int /*<<< orphan*/  yp_error (char*,char*,...) ; 

int
ypxfrd_get_map(char *host, char *map, char *domain, char *tmpname)
{
	CLIENT *clnt;
	struct ypxfr_mapname req;
	struct xfr resp;
	struct timeval timeout = { 0, 25 };
	int status = 0;

	req.xfrmap = map;
	req.xfrdomain = domain;
	req.xfrmap_filename = "";
	req.xfr_db_type = XFR_DB_BSD_HASH;	/*
	req.xfr_byte_order = XFR_ENDIAN_ANY;	 * Berkeley DB isn't
						 * byte-order sensitive.
						 */

	bzero((char *)&resp, sizeof(resp));

	if ((clnt = clnt_create(host, YPXFRD_FREEBSD_PROG,
				YPXFRD_FREEBSD_VERS, "tcp")) == NULL) {
		return(1);
	}

	if ((fp = open(tmpname, O_RDWR|O_CREAT, PERM_SECURE)) == -1) {
		clnt_destroy(clnt);
		yp_error("couldn't open %s: %s", tmpname, strerror(errno));
		return(1);
	}

	if (clnt_call(clnt,YPXFRD_GETMAP,
			(xdrproc_t)xdr_ypxfr_mapname, (char *)&req,
			(xdrproc_t)xdr_my_xfr, (char *)&resp,
			timeout) != RPC_SUCCESS) {
		yp_error("%s", clnt_sperror(clnt,"call to rpc.ypxfrd failed"));
		status++;
		unlink(tmpname);
	}

	clnt_destroy(clnt);
	close(fp);
	return(status);
}