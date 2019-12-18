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
struct hookinfo {void* hook_type; int /*<<< orphan*/  hook_id; struct enc_softc* hook_udata; int /*<<< orphan*/ * hook_helper; int /*<<< orphan*/  hook_func; } ;
struct enc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int EPFNOSUPPORT ; 
 size_t HHOOK_IPSEC_INET ; 
 size_t HHOOK_IPSEC_INET6 ; 
 void* HHOOK_TYPE_IPSEC_IN ; 
 void* HHOOK_TYPE_IPSEC_OUT ; 
 int /*<<< orphan*/  HHOOK_WAITOK ; 
 int /*<<< orphan*/ * V_ipsec_hhh_in ; 
 int /*<<< orphan*/ * V_ipsec_hhh_out ; 
 int /*<<< orphan*/  enc_hhook ; 
 int hhook_add_hook (int /*<<< orphan*/ ,struct hookinfo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
enc_add_hhooks(struct enc_softc *sc)
{
	struct hookinfo hki;
	int error;

	error = EPFNOSUPPORT;
	hki.hook_func = enc_hhook;
	hki.hook_helper = NULL;
	hki.hook_udata = sc;
#ifdef INET
	hki.hook_id = AF_INET;
	hki.hook_type = HHOOK_TYPE_IPSEC_IN;
	error = hhook_add_hook(V_ipsec_hhh_in[HHOOK_IPSEC_INET],
	    &hki, HHOOK_WAITOK);
	if (error != 0)
		return (error);
	hki.hook_type = HHOOK_TYPE_IPSEC_OUT;
	error = hhook_add_hook(V_ipsec_hhh_out[HHOOK_IPSEC_INET],
	    &hki, HHOOK_WAITOK);
	if (error != 0)
		return (error);
#endif
#ifdef INET6
	hki.hook_id = AF_INET6;
	hki.hook_type = HHOOK_TYPE_IPSEC_IN;
	error = hhook_add_hook(V_ipsec_hhh_in[HHOOK_IPSEC_INET6],
	    &hki, HHOOK_WAITOK);
	if (error != 0)
		return (error);
	hki.hook_type = HHOOK_TYPE_IPSEC_OUT;
	error = hhook_add_hook(V_ipsec_hhh_out[HHOOK_IPSEC_INET6],
	    &hki, HHOOK_WAITOK);
	if (error != 0)
		return (error);
#endif
	return (error);
}