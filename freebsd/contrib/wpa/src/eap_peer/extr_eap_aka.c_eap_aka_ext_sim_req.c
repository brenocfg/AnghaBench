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
struct eap_sm {int dummy; } ;
struct eap_aka_data {int /*<<< orphan*/  autn; int /*<<< orphan*/  rand; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_AKA_AUTN_LEN ; 
 int /*<<< orphan*/  EAP_AKA_RAND_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_sm_request_sim (struct eap_sm*,char*) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_snprintf_hex (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eap_aka_ext_sim_req(struct eap_sm *sm, struct eap_aka_data *data)
{
	char req[200], *pos, *end;

	wpa_printf(MSG_DEBUG, "EAP-AKA: Use external USIM processing");
	pos = req;
	end = pos + sizeof(req);
	pos += os_snprintf(pos, end - pos, "UMTS-AUTH");
	pos += os_snprintf(pos, end - pos, ":");
	pos += wpa_snprintf_hex(pos, end - pos, data->rand, EAP_AKA_RAND_LEN);
	pos += os_snprintf(pos, end - pos, ":");
	wpa_snprintf_hex(pos, end - pos, data->autn, EAP_AKA_AUTN_LEN);

	eap_sm_request_sim(sm, req);
	return 1;
}