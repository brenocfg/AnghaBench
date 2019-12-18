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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_MIN_BUFLEN ; 
 scalar_t__ LDNS_RR_TYPE_DNSKEY ; 
 scalar_t__ LDNS_RR_TYPE_KEY ; 
 int /*<<< orphan*/  ldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_buffer_new (int /*<<< orphan*/ ) ; 
 size_t ldns_buffer_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_calc_keytag_raw (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_rdata2buffer_wire (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

uint16_t
ldns_calc_keytag(const ldns_rr *key)
{
	uint16_t ac16;
	ldns_buffer *keybuf;
	size_t keysize;

	if (!key) {
		return 0;
	}

	if (ldns_rr_get_type(key) != LDNS_RR_TYPE_DNSKEY &&
	    ldns_rr_get_type(key) != LDNS_RR_TYPE_KEY
	    ) {
		return 0;
	}

	/* rdata to buf - only put the rdata in a buffer */
	keybuf = ldns_buffer_new(LDNS_MIN_BUFLEN); /* grows */
	if (!keybuf) {
		return 0;
	}
	(void)ldns_rr_rdata2buffer_wire(keybuf, key);
	/* the current pos in the buffer is the keysize */
	keysize= ldns_buffer_position(keybuf);

	ac16 = ldns_calc_keytag_raw(ldns_buffer_begin(keybuf), keysize);
	ldns_buffer_free(keybuf);
	return ac16;
}