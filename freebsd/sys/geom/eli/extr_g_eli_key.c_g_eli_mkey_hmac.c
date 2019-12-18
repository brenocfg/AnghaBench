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
typedef  int /*<<< orphan*/  hmkey ;

/* Variables and functions */
 int G_ELI_DATAIVKEYLEN ; 
 int G_ELI_USERKEYLEN ; 
 int SHA512_MDLEN ; 
 int /*<<< orphan*/  explicit_bzero (unsigned char*,int) ; 
 int /*<<< orphan*/  g_eli_crypto_hmac (unsigned char const*,int,...) ; 

void
g_eli_mkey_hmac(unsigned char *mkey, const unsigned char *key)
{
	unsigned char hmkey[SHA512_MDLEN];	/* Key for HMAC. */
	unsigned char *odhmac;	/* On-disk HMAC. */

	/*
	 * The key for HMAC calculations is: hmkey = HMAC_SHA512(Derived-Key, 0)
	 */
	g_eli_crypto_hmac(key, G_ELI_USERKEYLEN, "\x00", 1, hmkey, 0);

	odhmac = mkey + G_ELI_DATAIVKEYLEN;
	/* Calculate HMAC from Data-Key and IV-Key. */
	g_eli_crypto_hmac(hmkey, sizeof(hmkey), mkey, G_ELI_DATAIVKEYLEN,
	    odhmac, 0);

	explicit_bzero(hmkey, sizeof(hmkey));
}