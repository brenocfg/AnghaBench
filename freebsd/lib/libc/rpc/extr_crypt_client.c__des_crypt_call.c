#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct netconfig {int /*<<< orphan*/ * nc_protofmly; } ;
struct desparams {scalar_t__ des_dir; scalar_t__ des_mode; char* des_ivec; char* des_key; } ;
struct TYPE_9__ {char* desbuf_val; } ;
struct TYPE_10__ {int stat; char* des_ivec; TYPE_2__ desbuf; } ;
typedef  TYPE_3__ desresp ;
struct TYPE_8__ {int desbuf_len; char* desbuf_val; } ;
struct TYPE_11__ {char* des_ivec; char* des_key; int /*<<< orphan*/  des_mode; int /*<<< orphan*/  des_dir; TYPE_1__ desbuf; } ;
typedef  TYPE_4__ desargs ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 scalar_t__ CBC ; 
 int /*<<< orphan*/  CBC_DES ; 
 int /*<<< orphan*/  CRYPT_PROG ; 
 int /*<<< orphan*/  CRYPT_VERS ; 
 int /*<<< orphan*/  DECRYPT_DES ; 
 int DESERR_HWERROR ; 
 int DESERR_NOHWDEVICE ; 
 int DESERR_NONE ; 
 int /*<<< orphan*/  ECB_DES ; 
 scalar_t__ ENCRYPT ; 
 int /*<<< orphan*/  ENCRYPT_DES ; 
 int /*<<< orphan*/  NC_LOOPBACK ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  clnt_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clnt_freeres (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * clnt_tp_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netconfig*) ; 
 TYPE_3__* des_crypt_1 (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  endnetconfig (void*) ; 
 struct netconfig* getnetconfig (void*) ; 
 int /*<<< orphan*/  nc_sperror () ; 
 void* setnetconfig () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_desresp ; 

int
_des_crypt_call(char *buf, int len, struct desparams *dparms)
{
	CLIENT *clnt;
	desresp  *result_1;
	desargs  des_crypt_1_arg;
	struct netconfig *nconf;
	void *localhandle;
	int stat;

	nconf = NULL;
	localhandle = setnetconfig();
	while ((nconf = getnetconfig(localhandle)) != NULL) {
		if (nconf->nc_protofmly != NULL &&
		     strcmp(nconf->nc_protofmly, NC_LOOPBACK) == 0)
			break;
	}
	if (nconf == NULL) {
		warnx("getnetconfig: %s", nc_sperror());
		endnetconfig(localhandle);
		return(DESERR_HWERROR);
	}
	clnt = clnt_tp_create(NULL, CRYPT_PROG, CRYPT_VERS, nconf);
	if (clnt == (CLIENT *) NULL) {
		endnetconfig(localhandle);
		return(DESERR_HWERROR);
	}
	endnetconfig(localhandle);

	des_crypt_1_arg.desbuf.desbuf_len = len;
	des_crypt_1_arg.desbuf.desbuf_val = buf;
	des_crypt_1_arg.des_dir = (dparms->des_dir == ENCRYPT) ? ENCRYPT_DES : DECRYPT_DES;
	des_crypt_1_arg.des_mode = (dparms->des_mode == CBC) ? CBC_DES : ECB_DES;
	bcopy(dparms->des_ivec, des_crypt_1_arg.des_ivec, 8);
	bcopy(dparms->des_key, des_crypt_1_arg.des_key, 8);

	result_1 = des_crypt_1(&des_crypt_1_arg, clnt);
	if (result_1 == (desresp *) NULL) {
		clnt_destroy(clnt);
		return(DESERR_HWERROR);
	}

	stat = result_1->stat;

	if (result_1->stat == DESERR_NONE ||
	    result_1->stat == DESERR_NOHWDEVICE) {
		bcopy(result_1->desbuf.desbuf_val, buf, len);
		bcopy(result_1->des_ivec, dparms->des_ivec, 8);
	}

	clnt_freeres(clnt, (xdrproc_t)xdr_desresp, result_1);
	clnt_destroy(clnt);

	return(stat);
}