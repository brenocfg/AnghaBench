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
 size_t HHOOK_IPSEC_INET ; 
 size_t HHOOK_IPSEC_INET6 ; 
 void* HHOOK_TYPE_IPSEC_IN ; 
 void* HHOOK_TYPE_IPSEC_OUT ; 
 int /*<<< orphan*/ * V_ipsec_hhh_in ; 
 int /*<<< orphan*/ * V_ipsec_hhh_out ; 
 int /*<<< orphan*/  enc_hhook ; 
 int /*<<< orphan*/  hhook_remove_hook (int /*<<< orphan*/ ,struct hookinfo*) ; 

__attribute__((used)) static void
enc_remove_hhooks(struct enc_softc *sc)
{
	struct hookinfo hki;

	hki.hook_func = enc_hhook;
	hki.hook_helper = NULL;
	hki.hook_udata = sc;
#ifdef INET
	hki.hook_id = AF_INET;
	hki.hook_type = HHOOK_TYPE_IPSEC_IN;
	hhook_remove_hook(V_ipsec_hhh_in[HHOOK_IPSEC_INET], &hki);
	hki.hook_type = HHOOK_TYPE_IPSEC_OUT;
	hhook_remove_hook(V_ipsec_hhh_out[HHOOK_IPSEC_INET], &hki);
#endif
#ifdef INET6
	hki.hook_id = AF_INET6;
	hki.hook_type = HHOOK_TYPE_IPSEC_IN;
	hhook_remove_hook(V_ipsec_hhh_in[HHOOK_IPSEC_INET6], &hki);
	hki.hook_type = HHOOK_TYPE_IPSEC_OUT;
	hhook_remove_hook(V_ipsec_hhh_out[HHOOK_IPSEC_INET6], &hki);
#endif
}