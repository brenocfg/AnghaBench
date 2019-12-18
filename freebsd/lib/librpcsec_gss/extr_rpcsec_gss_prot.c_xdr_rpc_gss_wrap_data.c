#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* xdrproc_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;
typedef  int u_int ;
typedef  scalar_t__ rpc_gss_service_t ;
typedef  int /*<<< orphan*/  gss_qop_t ;
typedef  int /*<<< orphan*/  gss_ctx_id_t ;
struct TYPE_8__ {int length; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  TRUE ; 
 int XDR_GETPOS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDR_INLINE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XDR_SETPOS (int /*<<< orphan*/ *,int) ; 
 scalar_t__ gss_get_mic (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  gss_release_buffer (scalar_t__*,TYPE_1__*) ; 
 scalar_t__ gss_wrap (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  log_status (char*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ rpc_gss_svc_integrity ; 
 scalar_t__ rpc_gss_svc_privacy ; 
 int /*<<< orphan*/  xdr_gss_buffer_desc (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  xdr_u_int (int /*<<< orphan*/ *,int*) ; 

bool_t
xdr_rpc_gss_wrap_data(XDR *xdrs, xdrproc_t xdr_func, caddr_t xdr_ptr,
		      gss_ctx_id_t ctx, gss_qop_t qop,
		      rpc_gss_service_t svc, u_int seq)
{
	gss_buffer_desc	databuf, wrapbuf;
	OM_uint32	maj_stat, min_stat;
	int		start, end, conf_state;
	u_int		len;
	bool_t		xdr_stat;

	/* Skip databody length. */
	start = XDR_GETPOS(xdrs);
	XDR_SETPOS(xdrs, start + 4);
	
	/* Marshal rpc_gss_data_t (sequence number + arguments). */
	if (!xdr_u_int(xdrs, &seq) || !xdr_func(xdrs, xdr_ptr))
		return (FALSE);
	end = XDR_GETPOS(xdrs);

	/* Set databuf to marshalled rpc_gss_data_t. */
	databuf.length = end - start - 4;
	XDR_SETPOS(xdrs, start + 4);
	databuf.value = XDR_INLINE(xdrs, databuf.length);

	xdr_stat = FALSE;
	
	if (svc == rpc_gss_svc_integrity) {
		/* Marshal databody_integ length. */
		XDR_SETPOS(xdrs, start);
		len = databuf.length;
		if (!xdr_u_int(xdrs, &len))
			return (FALSE);
		
		/* Checksum rpc_gss_data_t. */
		maj_stat = gss_get_mic(&min_stat, ctx, qop,
				       &databuf, &wrapbuf);
		if (maj_stat != GSS_S_COMPLETE) {
			log_debug("gss_get_mic failed");
			return (FALSE);
		}
		/* Marshal checksum. */
		XDR_SETPOS(xdrs, end);
		xdr_stat = xdr_gss_buffer_desc(xdrs, &wrapbuf);
		gss_release_buffer(&min_stat, &wrapbuf);
	}		
	else if (svc == rpc_gss_svc_privacy) {
		/* Encrypt rpc_gss_data_t. */
		maj_stat = gss_wrap(&min_stat, ctx, TRUE, qop, &databuf,
				    &conf_state, &wrapbuf);
		if (maj_stat != GSS_S_COMPLETE) {
			log_status("gss_wrap", NULL, maj_stat, min_stat);
			return (FALSE);
		}
		/* Marshal databody_priv. */
		XDR_SETPOS(xdrs, start);
		xdr_stat = xdr_gss_buffer_desc(xdrs, &wrapbuf);
		gss_release_buffer(&min_stat, &wrapbuf);
	}
	return (xdr_stat);
}