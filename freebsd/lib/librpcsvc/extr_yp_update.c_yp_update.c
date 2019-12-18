#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct TYPE_8__ {int yp_buf_len; char* yp_buf_val; } ;
struct TYPE_7__ {int yp_buf_len; char* yp_buf_val; } ;
struct ypupdate_args {char* mapname; TYPE_2__ datum; TYPE_1__ key; } ;
struct ypdelete_args {char* mapname; TYPE_2__ datum; TYPE_1__ key; } ;
struct timeval {int /*<<< orphan*/  tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  des_block ;
struct TYPE_9__ {int /*<<< orphan*/ * cl_auth; } ;
typedef  TYPE_3__ CLIENT ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 int /*<<< orphan*/  MAXNETNAMELEN ; 
 int RPC_AUTHERROR ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  TIMEOUT ; 
 int /*<<< orphan*/  WINDOW ; 
 unsigned int YPERR_ACCESS ; 
 int YPERR_BADARGS ; 
 int YPERR_DOMAIN ; 
 int YPERR_RESRC ; 
 int YPERR_RPC ; 
#define  YPOP_CHANGE 131 
#define  YPOP_DELETE 130 
#define  YPOP_INSERT 129 
#define  YPOP_STORE 128 
 int /*<<< orphan*/  YPU_CHANGE ; 
 int /*<<< orphan*/  YPU_DELETE ; 
 int /*<<< orphan*/  YPU_INSERT ; 
 int /*<<< orphan*/  YPU_PROG ; 
 int /*<<< orphan*/  YPU_STORE ; 
 int /*<<< orphan*/  YPU_VERS ; 
 int /*<<< orphan*/  auth_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ authdes_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int clnt_call (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ypupdate_args*,int /*<<< orphan*/ ,unsigned int*,struct timeval) ; 
 TYPE_3__* clnt_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clnt_destroy (TYPE_3__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getrpcport (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  host2netname (char*,char*,char*) ; 
 int /*<<< orphan*/  key_gendes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_int ; 
 int /*<<< orphan*/  xdr_ypdelete_args ; 
 int /*<<< orphan*/  xdr_ypupdate_args ; 
 int yp_master (char*,char*,char**) ; 

int
yp_update(char *domain, char *map, unsigned int ypop, char *key, int keylen,
    char *data, int datalen)
{
	char *master;
	int rval;
	unsigned int res;
	struct ypupdate_args upargs;
	struct ypdelete_args delargs;
	CLIENT *clnt;
	char netname[MAXNETNAMELEN+1];
	des_block des_key;
	struct timeval timeout;

	/* Get the master server name for 'domain.' */
	if ((rval = yp_master(domain, map, &master)))
		return(rval);

	/* Check that ypupdated is running there. */
	if (getrpcport(master, YPU_PROG, YPU_VERS, ypop))
		return(YPERR_DOMAIN);

	/* Get a handle. */
	if ((clnt = clnt_create(master, YPU_PROG, YPU_VERS, "tcp")) == NULL)
		return(YPERR_RPC);

	/*
	 * Assemble netname of server.
	 * NOTE: It's difficult to discern from the documentation, but
	 * when you make a Secure RPC call, the netname you pass should
	 * be the netname of the guy on the other side, not your own
	 * netname. This is how the client side knows what public key
	 * to use for the initial exchange. Passing your own netname
	 * only works if the server on the other side is running under
	 * your UID.
	 */
	if (!host2netname(netname, master, domain)) {
		clnt_destroy(clnt);
		return(YPERR_BADARGS);
	}

	/* Make up a DES session key. */
	key_gendes(&des_key);

	/* Set up DES authentication. */
	if ((clnt->cl_auth = (AUTH *)authdes_create(netname, WINDOW, NULL,
			&des_key)) == NULL) {
		clnt_destroy(clnt);
		return(YPERR_RESRC);
	}

	/* Set a timeout for clnt_call(). */
	timeout.tv_usec = 0;
	timeout.tv_sec = TIMEOUT;

	/*
	 * Make the call. Note that we use clnt_call() here rather than
	 * the rpcgen-erated client stubs. We could use those stubs, but
	 * then we'd have to do some gymnastics to get at the error
	 * information to figure out what error code to send back to the
	 * caller. With clnt_call(), we get the error status returned to
	 * us right away, and we only have to exert a small amount of
	 * extra effort.
	 */
	switch (ypop) {
	case YPOP_CHANGE:
		upargs.mapname = map;
		upargs.key.yp_buf_len = keylen;
		upargs.key.yp_buf_val = key;
		upargs.datum.yp_buf_len = datalen;
		upargs.datum.yp_buf_val = data;

		if ((rval = clnt_call(clnt, YPU_CHANGE,
			(xdrproc_t)xdr_ypupdate_args, &upargs,
			(xdrproc_t)xdr_u_int, &res, timeout)) != RPC_SUCCESS) {
			if (rval == RPC_AUTHERROR)
				res = YPERR_ACCESS;
			else
				res = YPERR_RPC;
		}

		break;
	case YPOP_INSERT:
		upargs.mapname = map;
		upargs.key.yp_buf_len = keylen;
		upargs.key.yp_buf_val = key;
		upargs.datum.yp_buf_len = datalen;
		upargs.datum.yp_buf_val = data;

		if ((rval = clnt_call(clnt, YPU_INSERT,
			(xdrproc_t)xdr_ypupdate_args, &upargs,
			(xdrproc_t)xdr_u_int, &res, timeout)) != RPC_SUCCESS) {
			if (rval == RPC_AUTHERROR)
				res = YPERR_ACCESS;
			else
				res = YPERR_RPC;
		}

		break;
	case YPOP_DELETE:
		delargs.mapname = map;
		delargs.key.yp_buf_len = keylen;
		delargs.key.yp_buf_val = key;

		if ((rval = clnt_call(clnt, YPU_DELETE,
			(xdrproc_t)xdr_ypdelete_args, &delargs,
			(xdrproc_t)xdr_u_int, &res, timeout)) != RPC_SUCCESS) {
			if (rval == RPC_AUTHERROR)
				res = YPERR_ACCESS;
			else
				res = YPERR_RPC;
		}

		break;
	case YPOP_STORE:
		upargs.mapname = map;
		upargs.key.yp_buf_len = keylen;
		upargs.key.yp_buf_val = key;
		upargs.datum.yp_buf_len = datalen;
		upargs.datum.yp_buf_val = data;

		if ((rval = clnt_call(clnt, YPU_STORE,
			(xdrproc_t)xdr_ypupdate_args, &upargs,
			(xdrproc_t)xdr_u_int, &res, timeout)) != RPC_SUCCESS) {
			if (rval == RPC_AUTHERROR)
				res = YPERR_ACCESS;
			else
				res = YPERR_RPC;
		}

		break;
	default:
		res = YPERR_BADARGS;
		break;
	}

	/* All done: tear down the connection. */
	auth_destroy(clnt->cl_auth);
	clnt_destroy(clnt);
	free(master);

	return(res);
}