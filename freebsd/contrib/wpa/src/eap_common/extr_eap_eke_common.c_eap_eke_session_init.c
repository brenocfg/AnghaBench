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
typedef  void* u8 ;
struct eap_eke_session {scalar_t__ prf_len; scalar_t__ nonce_len; scalar_t__ auth_len; scalar_t__ dhcomp_len; scalar_t__ pnonce_len; scalar_t__ pnonce_ps_len; void* mac; void* encr; void* dhgroup; void* prf; } ;

/* Variables and functions */
 scalar_t__ eap_eke_auth_len (void*) ; 
 scalar_t__ eap_eke_dhcomp_len (void*,void*) ; 
 scalar_t__ eap_eke_nonce_len (void*) ; 
 scalar_t__ eap_eke_pnonce_len (void*) ; 
 scalar_t__ eap_eke_pnonce_ps_len (void*) ; 
 scalar_t__ eap_eke_prf_len (void*) ; 

int eap_eke_session_init(struct eap_eke_session *sess, u8 dhgroup, u8 encr,
			 u8 prf, u8 mac)
{
	sess->dhgroup = dhgroup;
	sess->encr = encr;
	sess->prf = prf;
	sess->mac = mac;

	sess->prf_len = eap_eke_prf_len(prf);
	sess->nonce_len = eap_eke_nonce_len(prf);
	sess->auth_len = eap_eke_auth_len(prf);
	sess->dhcomp_len = eap_eke_dhcomp_len(sess->dhgroup, sess->encr);
	sess->pnonce_len = eap_eke_pnonce_len(sess->mac);
	sess->pnonce_ps_len = eap_eke_pnonce_ps_len(sess->mac);
	if (sess->prf_len < 0 || sess->nonce_len < 0 || sess->auth_len < 0 ||
	    sess->dhcomp_len < 0 || sess->pnonce_len < 0 ||
	    sess->pnonce_ps_len < 0)
		return -1;

	return 0;
}