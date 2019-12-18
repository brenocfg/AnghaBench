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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_private_key {int dummy; } ;
struct asn1_hdr {scalar_t__ class; scalar_t__ tag; size_t length; int /*<<< orphan*/ * payload; } ;

/* Variables and functions */
 scalar_t__ ASN1_CLASS_UNIVERSAL ; 
 scalar_t__ ASN1_TAG_OCTETSTRING ; 
 scalar_t__ ASN1_TAG_SEQUENCE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ asn1_get_next (int /*<<< orphan*/  const*,int,struct asn1_hdr*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pkcs5_decrypt (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,size_t,char const*,size_t*) ; 
 struct crypto_private_key* pkcs8_key_import (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

struct crypto_private_key *
pkcs8_enc_key_import(const u8 *buf, size_t len, const char *passwd)
{
	struct asn1_hdr hdr;
	const u8 *pos, *end, *enc_alg;
	size_t enc_alg_len;
	u8 *data;
	size_t data_len;

	if (passwd == NULL)
		return NULL;

	/*
	 * PKCS #8, Chapter 7
	 * EncryptedPrivateKeyInfo ::= SEQUENCE {
	 *   encryptionAlgorithm EncryptionAlgorithmIdentifier,
	 *   encryptedData EncryptedData }
	 * EncryptionAlgorithmIdentifier ::= AlgorithmIdentifier
	 * EncryptedData ::= OCTET STRING
	 */

	if (asn1_get_next(buf, len, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_SEQUENCE) {
		wpa_printf(MSG_DEBUG, "PKCS #8: Does not start with PKCS #8 "
			   "header (SEQUENCE); assume encrypted PKCS #8 not "
			   "used");
		return NULL;
	}
	pos = hdr.payload;
	end = pos + hdr.length;

	/* encryptionAlgorithm EncryptionAlgorithmIdentifier */
	if (asn1_get_next(pos, end - pos, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_SEQUENCE) {
		wpa_printf(MSG_DEBUG, "PKCS #8: Expected SEQUENCE "
			   "(AlgorithmIdentifier) - found class %d tag 0x%x; "
			   "assume encrypted PKCS #8 not used",
			   hdr.class, hdr.tag);
		return NULL;
	}
	enc_alg = hdr.payload;
	enc_alg_len = hdr.length;
	pos = hdr.payload + hdr.length;

	/* encryptedData EncryptedData */
	if (asn1_get_next(pos, end - pos, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_OCTETSTRING) {
		wpa_printf(MSG_DEBUG, "PKCS #8: Expected OCTETSTRING "
			   "(encryptedData) - found class %d tag 0x%x",
			   hdr.class, hdr.tag);
		return NULL;
	}

	data = pkcs5_decrypt(enc_alg, enc_alg_len, hdr.payload, hdr.length,
			     passwd, &data_len);
	if (data) {
		struct crypto_private_key *key;
		key = pkcs8_key_import(data, data_len);
		os_free(data);
		return key;
	}

	return NULL;
}