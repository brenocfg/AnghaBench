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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int const*) ; 
 int tls_cipher_suite_match (int const*,int /*<<< orphan*/ ,int) ; 

int eap_teap_allowed_anon_prov_cipher_suite(u16 cs)
{
	/* RFC 7170, Section 3.8.3: anonymous ciphersuites MAY be supported as
	 * long as the TLS pre-master secret is generated form contribution from
	 * both peers. Accept the recommended TLS_DH_anon_WITH_AES_128_CBC_SHA
	 * cipher suite and other ciphersuites that use DH in some form, have
	 * SHA-1 or stronger MAC function, and use reasonable strong cipher. */
	static const u16 ok_cs[] = {
		/* DH-anon */
		0x0034, 0x003a, 0x006c, 0x006d, 0x00a6, 0x00a7,
		/* DHE-RSA */
		0x0033, 0x0039, 0x0067, 0x006b, 0x009e, 0x009f,
		/* ECDH-anon */
		0xc018, 0xc019,
		/* ECDH-RSA */
		0xc003, 0xc00f, 0xc029, 0xc02a, 0xc031, 0xc032,
		/* ECDH-ECDSA */
		0xc004, 0xc005, 0xc025, 0xc026, 0xc02d, 0xc02e,
		/* ECDHE-RSA */
		0xc013, 0xc014, 0xc027, 0xc028, 0xc02f, 0xc030,
		/* ECDHE-ECDSA */
		0xc009, 0xc00a, 0xc023, 0xc024, 0xc02b, 0xc02c,
	};

	return tls_cipher_suite_match(ok_cs, ARRAY_SIZE(ok_cs), cs);
}