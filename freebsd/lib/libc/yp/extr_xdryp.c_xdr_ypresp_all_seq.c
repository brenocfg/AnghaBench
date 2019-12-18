#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  int u_long ;
struct TYPE_6__ {size_t valdat_len; int /*<<< orphan*/  valdat_val; } ;
struct TYPE_5__ {size_t keydat_len; int /*<<< orphan*/  keydat_val; } ;
struct TYPE_7__ {int stat; TYPE_2__ val; TYPE_1__ key; } ;
struct TYPE_8__ {TYPE_3__ val; } ;
struct ypresp_all {scalar_t__ more; TYPE_4__ ypresp_all_u; } ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
#define  YP_NOMORE 129 
#define  YP_TRUE 128 
 int YP_YPERR ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  bzero (struct ypresp_all*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int stub1 (int,char*,size_t,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,struct ypresp_all*) ; 
 int /*<<< orphan*/  xdr_ypresp_all (int /*<<< orphan*/ *,struct ypresp_all*) ; 
 int ypresp_allfn (int,char*,size_t,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ypresp_data ; 

bool_t
xdr_ypresp_all_seq(XDR *xdrs, u_long *objp)
{
	struct ypresp_all out;
	u_long status;
	char *key, *val;
	int r;

	bzero(&out, sizeof out);
	while (1) {
		if (!xdr_ypresp_all(xdrs, &out)) {
			xdr_free((xdrproc_t)xdr_ypresp_all, &out);
			*objp = YP_YPERR;
			return (FALSE);
		}
		if (out.more == 0) {
			xdr_free((xdrproc_t)xdr_ypresp_all, &out);
			*objp = YP_NOMORE;
			return (TRUE);
		}
		status = out.ypresp_all_u.val.stat;
		switch (status) {
		case YP_TRUE:
			key = (char *)malloc(out.ypresp_all_u.val.key.keydat_len + 1);
			if (key == NULL) {
				xdr_free((xdrproc_t)xdr_ypresp_all, &out);
				*objp = YP_YPERR;
				return (FALSE);
			}
			bcopy(out.ypresp_all_u.val.key.keydat_val, key,
				out.ypresp_all_u.val.key.keydat_len);
			key[out.ypresp_all_u.val.key.keydat_len] = '\0';
			val = (char *)malloc(out.ypresp_all_u.val.val.valdat_len + 1);
			if (val == NULL) {
				free(key);
				xdr_free((xdrproc_t)xdr_ypresp_all, &out);
				*objp = YP_YPERR;
				return (FALSE);
			}
			bcopy(out.ypresp_all_u.val.val.valdat_val, val,
				out.ypresp_all_u.val.val.valdat_len);
			val[out.ypresp_all_u.val.val.valdat_len] = '\0';
			xdr_free((xdrproc_t)xdr_ypresp_all, &out);

			r = (*ypresp_allfn)(status,
				key, out.ypresp_all_u.val.key.keydat_len,
				val, out.ypresp_all_u.val.val.valdat_len,
				ypresp_data);
			*objp = status;
			free(key);
			free(val);
			if (r)
				return (TRUE);
			break;
		case YP_NOMORE:
			xdr_free((xdrproc_t)xdr_ypresp_all, &out);
			*objp = YP_NOMORE;
			return (TRUE);
		default:
			xdr_free((xdrproc_t)xdr_ypresp_all, &out);
			*objp = status;
			return (TRUE);
		}
	}
}