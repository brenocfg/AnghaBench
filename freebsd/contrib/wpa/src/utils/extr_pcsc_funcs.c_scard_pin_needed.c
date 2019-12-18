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
struct scard_data {scalar_t__ sim_type; } ;

/* Variables and functions */
 unsigned char SCARD_CHV1_FLAG ; 
 size_t SCARD_CHV1_OFFSET ; 
 scalar_t__ SCARD_GSM_SIM ; 
 scalar_t__ SCARD_USIM ; 
 scalar_t__ scard_parse_fsp_templ (unsigned char*,size_t,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scard_pin_needed(struct scard_data *scard,
			    unsigned char *hdr, size_t hlen)
{
	if (scard->sim_type == SCARD_GSM_SIM) {
		if (hlen > SCARD_CHV1_OFFSET &&
		    !(hdr[SCARD_CHV1_OFFSET] & SCARD_CHV1_FLAG))
			return 1;
		return 0;
	}

	if (scard->sim_type == SCARD_USIM) {
		int ps_do;
		if (scard_parse_fsp_templ(hdr, hlen, &ps_do, NULL))
			return -1;
		/* TODO: there could be more than one PS_DO entry because of
		 * multiple PINs in key reference.. */
		if (ps_do > 0 && (ps_do & 0x80))
			return 1;
		return 0;
	}

	return -1;
}