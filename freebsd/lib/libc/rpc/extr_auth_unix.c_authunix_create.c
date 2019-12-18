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
typedef  int u_int ;
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct authunix_parms {char* aup_machname; int aup_uid; int aup_gid; int aup_len; int* aup_gids; int /*<<< orphan*/  aup_time; } ;
struct TYPE_2__ {int oa_length; struct audata* oa_base; int /*<<< orphan*/  oa_flavor; } ;
struct audata {TYPE_1__ au_origcred; TYPE_1__ ah_cred; scalar_t__ au_shfaults; int /*<<< orphan*/  au_shcred; int /*<<< orphan*/  ah_verf; scalar_t__ ah_private; int /*<<< orphan*/  ah_ops; } ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  XDR ;
typedef  struct audata AUTH ;

/* Variables and functions */
 int /*<<< orphan*/  AUTH_UNIX ; 
 int MAX_AUTH_BYTES ; 
 int /*<<< orphan*/  XDR_ENCODE ; 
 int XDR_GETPOS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _null_auth ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  authunix_ops () ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  marshal_new_auth (struct audata*) ; 
 void* mem_alloc (int) ; 
 int /*<<< orphan*/  mem_free (struct audata*,int) ; 
 int /*<<< orphan*/  memmove (struct audata*,char*,size_t) ; 
 int /*<<< orphan*/  warnx (char*) ; 
 int /*<<< orphan*/  xdr_authunix_parms (int /*<<< orphan*/ *,struct authunix_parms*) ; 
 int /*<<< orphan*/  xdrmem_create (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

AUTH *
authunix_create(char *machname, u_int uid, u_int gid, int len, u_int *aup_gids)
{
	struct authunix_parms aup;
	char mymem[MAX_AUTH_BYTES];
	struct timeval now;
	XDR xdrs;
	AUTH *auth;
	struct audata *au;

	/*
	 * Allocate and set up auth handle
	 */
	au = NULL;
	auth = mem_alloc(sizeof(*auth));
#ifndef _KERNEL
	if (auth == NULL) {
		warnx("authunix_create: out of memory");
		goto cleanup_authunix_create;
	}
#endif
	au = mem_alloc(sizeof(*au));
#ifndef _KERNEL
	if (au == NULL) {
		warnx("authunix_create: out of memory");
		goto cleanup_authunix_create;
	}
#endif
	auth->ah_ops = authunix_ops();
	auth->ah_private = (caddr_t)au;
	auth->ah_verf = au->au_shcred = _null_auth;
	au->au_shfaults = 0;
	au->au_origcred.oa_base = NULL;

	/*
	 * fill in param struct from the given params
	 */
	(void)gettimeofday(&now, NULL);
	aup.aup_time = now.tv_sec;
	aup.aup_machname = machname;
	aup.aup_uid = uid;
	aup.aup_gid = gid;
	aup.aup_len = (u_int)len;
	aup.aup_gids = aup_gids;

	/*
	 * Serialize the parameters into origcred
	 */
	xdrmem_create(&xdrs, mymem, MAX_AUTH_BYTES, XDR_ENCODE);
	if (! xdr_authunix_parms(&xdrs, &aup)) 
		abort();
	au->au_origcred.oa_length = len = XDR_GETPOS(&xdrs);
	au->au_origcred.oa_flavor = AUTH_UNIX;
#ifdef _KERNEL
	au->au_origcred.oa_base = mem_alloc((u_int) len);
#else
	if ((au->au_origcred.oa_base = mem_alloc((u_int) len)) == NULL) {
		warnx("authunix_create: out of memory");
		goto cleanup_authunix_create;
	}
#endif
	memmove(au->au_origcred.oa_base, mymem, (size_t)len);

	/*
	 * set auth handle to reflect new cred.
	 */
	auth->ah_cred = au->au_origcred;
	marshal_new_auth(auth);
	return (auth);
#ifndef _KERNEL
 cleanup_authunix_create:
	if (auth)
		mem_free(auth, sizeof(*auth));
	if (au) {
		if (au->au_origcred.oa_base)
			mem_free(au->au_origcred.oa_base, (u_int)len);
		mem_free(au, sizeof(*au));
	}
	return (NULL);
#endif
}