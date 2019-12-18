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
struct TYPE_2__ {int /*<<< orphan*/  window; int /*<<< orphan*/  key; int /*<<< orphan*/  name; } ;
struct authdes_cred {int adc_namekind; int /*<<< orphan*/  adc_nickname; TYPE_1__ adc_fullname; } ;
typedef  int /*<<< orphan*/  enum_t ;
typedef  enum authdes_namekind { ____Placeholder_authdes_namekind } authdes_namekind ;
typedef  int /*<<< orphan*/  des_block ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
#define  ADN_FULLNAME 129 
#define  ADN_NICKNAME 128 
 int /*<<< orphan*/  ATTEMPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MAXNETNAMELEN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdr_enum (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_opaque (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xdr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool_t
xdr_authdes_cred(XDR *xdrs, struct authdes_cred *cred)
{
	enum authdes_namekind *padc_namekind = &cred->adc_namekind;
	/*
	 * Unrolled xdr
	 */
	ATTEMPT(xdr_enum(xdrs, (enum_t *) padc_namekind));
	switch (cred->adc_namekind) {
	case ADN_FULLNAME:
		ATTEMPT(xdr_string(xdrs, &cred->adc_fullname.name,
		    MAXNETNAMELEN));
		ATTEMPT(xdr_opaque(xdrs, (caddr_t)&cred->adc_fullname.key,
		    sizeof(des_block)));
		ATTEMPT(xdr_opaque(xdrs, (caddr_t)&cred->adc_fullname.window,
		    sizeof(cred->adc_fullname.window)));
		return (TRUE);
	case ADN_NICKNAME:
		ATTEMPT(xdr_opaque(xdrs, (caddr_t)&cred->adc_nickname,
		    sizeof(cred->adc_nickname)));
		return (TRUE);
	default:
		return (FALSE);
	}
}