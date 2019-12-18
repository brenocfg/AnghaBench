#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gss_channel_bindings_t ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_13__ {int x_op; } ;
typedef  TYPE_2__ XDR ;
struct TYPE_12__ {int /*<<< orphan*/  application_data; int /*<<< orphan*/  acceptor_address; int /*<<< orphan*/  initiator_address; int /*<<< orphan*/  acceptor_addrtype; int /*<<< orphan*/  initiator_addrtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* GSS_C_NO_CHANNEL_BINDINGS ; 
 int /*<<< orphan*/  TRUE ; 
#define  XDR_DECODE 130 
#define  XDR_ENCODE 129 
#define  XDR_FREE 128 
 TYPE_1__* mem_alloc (int) ; 
 int /*<<< orphan*/  mem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xdr_bool (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_gss_buffer_desc (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_uint32_t (TYPE_2__*,int /*<<< orphan*/ *) ; 

bool_t
xdr_gss_channel_bindings_t(XDR *xdrs, gss_channel_bindings_t *chp)
{
	gss_channel_bindings_t ch;
	bool_t is_null;

	switch (xdrs->x_op) {
	case XDR_ENCODE:
		ch = *chp;
		if (ch) {
			is_null = FALSE;
			if (!xdr_bool(xdrs, &is_null)
			    || !xdr_uint32_t(xdrs, &ch->initiator_addrtype)
			    || !xdr_gss_buffer_desc(xdrs,
				&ch->initiator_address)
			    || !xdr_uint32_t(xdrs, &ch->acceptor_addrtype)
			    || !xdr_gss_buffer_desc(xdrs,
				&ch->acceptor_address)
			    || !xdr_gss_buffer_desc(xdrs,
				&ch->application_data))
				return (FALSE);
		} else {
			is_null = TRUE;
			if (!xdr_bool(xdrs, &is_null))
				return (FALSE);
		}
		break;

	case XDR_DECODE:
		if (!xdr_bool(xdrs, &is_null))
			return (FALSE);
		if (is_null) {
			*chp = GSS_C_NO_CHANNEL_BINDINGS;
		} else {
			ch = mem_alloc(sizeof(*ch));
			memset(ch, 0, sizeof(*ch));
			if (!xdr_uint32_t(xdrs, &ch->initiator_addrtype)
			    || !xdr_gss_buffer_desc(xdrs,
				&ch->initiator_address)
			    || !xdr_uint32_t(xdrs, &ch->acceptor_addrtype)
			    || !xdr_gss_buffer_desc(xdrs,
				&ch->acceptor_address)
			    || !xdr_gss_buffer_desc(xdrs,
				&ch->application_data)) {
				mem_free(ch, sizeof(*ch));
				return (FALSE);
			}
			*chp = ch;
		}
		break;

	case XDR_FREE:
		ch = *chp;
		if (ch) {
			xdr_gss_buffer_desc(xdrs, &ch->initiator_address);
			xdr_gss_buffer_desc(xdrs, &ch->acceptor_address);
			xdr_gss_buffer_desc(xdrs, &ch->application_data);
			mem_free(ch, sizeof(*ch));
		}
	}

	return (TRUE);
}