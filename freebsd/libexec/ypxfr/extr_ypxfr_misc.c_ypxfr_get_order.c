#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int stat; unsigned long ordernum; } ;
typedef  TYPE_1__ ypresp_order ;
struct TYPE_6__ {char* map; char* domain; } ;
typedef  TYPE_2__ ypreq_nokey ;
typedef  enum ypstat { ____Placeholder_ypstat } ypstat ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
#define  YPERR_DOMAIN 133 
#define  YPERR_MAP 132 
#define  YPERR_YPERR 131 
 int /*<<< orphan*/  YPPROG ; 
 int /*<<< orphan*/  YPVERS ; 
 scalar_t__ YPXFR_NODOM ; 
 scalar_t__ YPXFR_NOMAP ; 
 scalar_t__ YPXFR_RPC ; 
 scalar_t__ YPXFR_YPERR ; 
#define  YP_NODOM 130 
#define  YP_NOMAP 129 
 int YP_TRUE ; 
#define  YP_YPERR 128 
 int /*<<< orphan*/ * clnt_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clnt_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clnt_spcreateerror (char*) ; 
 int /*<<< orphan*/  clnt_sperror (int /*<<< orphan*/ *,char*) ; 
 int yp_errno ; 
 int /*<<< orphan*/  yp_error (char*,int /*<<< orphan*/ ) ; 
 int yp_order (char*,char*,unsigned int*) ; 
 TYPE_1__* ypproc_order_2 (TYPE_2__*,int /*<<< orphan*/ *) ; 

unsigned long
ypxfr_get_order(char *domain, char *map, char *source, const int yplib)
{
	if (yplib) {
		unsigned int order;
		int res;
		if ((res = yp_order(domain, map, &order))) {
			switch (res) {
			case YPERR_DOMAIN:
				yp_errno = (enum ypstat)YPXFR_NODOM;
				break;
			case YPERR_MAP:
				yp_errno = (enum ypstat)YPXFR_NOMAP;
				break;
			case YPERR_YPERR:
			default:
				yp_errno = (enum ypstat)YPXFR_YPERR;
				break;
			}
			return(0);
		} else
			return(order);
	} else {
		CLIENT *clnt;
		ypresp_order *resp;
		ypreq_nokey req;

		if ((clnt = clnt_create(source,YPPROG,YPVERS,"udp")) == NULL) {
			yp_error("%s",clnt_spcreateerror("couldn't create \
udp handle to ypserv"));
			yp_errno = (enum ypstat)YPXFR_RPC;
			return(0);
		}
		req.map = map;
		req.domain = domain;
		if ((resp = ypproc_order_2(&req, clnt)) == NULL) {
			yp_error("%s", clnt_sperror(clnt, "YPPROC_ORDER \
failed"));
			clnt_destroy(clnt);
			yp_errno = (enum ypstat)YPXFR_RPC;
			return(0);
		}
		clnt_destroy(clnt);
		if (resp->stat != YP_TRUE) {
			switch (resp->stat) {
			case YP_NODOM:
				yp_errno = (enum ypstat)YPXFR_NODOM;
				break;
			case YP_NOMAP:
				yp_errno = (enum ypstat)YPXFR_NOMAP;
				break;
			case YP_YPERR:
			default:
				yp_errno = (enum ypstat)YPXFR_YPERR;
				break;
			}
			return(0);
		}
		return(resp->ordernum);
	}
}