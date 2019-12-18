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
typedef  scalar_t__ u_long ;
struct ypreq_nokey {char* domain; char* map; } ;
struct ypall_callback {scalar_t__ data; int /*<<< orphan*/  foreach; } ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  YPPROC_ALL ; 
 scalar_t__ YP_FALSE ; 
 int /*<<< orphan*/  _yplib_host_timeout ; 
 int /*<<< orphan*/  clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ypreq_nokey*,int /*<<< orphan*/ ,scalar_t__*,struct timeval) ; 
 scalar_t__ xdr_ypreq_nokey ; 
 scalar_t__ xdr_ypresp_all_seq ; 
 int ypprot_err (scalar_t__) ; 
 int /*<<< orphan*/  ypresp_allfn ; 
 void* ypresp_data ; 

int
yp_all_host(CLIENT *client, char *indomain, char *inmap,
    struct ypall_callback *incallback)
{
	struct ypreq_nokey yprnk;
	struct timeval tv;
	u_long status;

	tv.tv_sec = _yplib_host_timeout;
	tv.tv_usec = 0;

	yprnk.domain = indomain;
	yprnk.map = inmap;
	ypresp_allfn = incallback->foreach;
	ypresp_data = (void *)incallback->data;

	(void) clnt_call(client, YPPROC_ALL,
	    (xdrproc_t)xdr_ypreq_nokey, &yprnk,
	    (xdrproc_t)xdr_ypresp_all_seq, &status, tv);
	if (status != YP_FALSE)
		return ypprot_err(status);

	return (0);
}