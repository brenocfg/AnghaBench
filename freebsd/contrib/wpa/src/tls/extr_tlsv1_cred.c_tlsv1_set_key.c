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
struct tlsv1_credentials {int /*<<< orphan*/ * key; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/ * crypto_private_key_import (int /*<<< orphan*/  const*,size_t,char const*) ; 
 int /*<<< orphan*/  pkcs12_parse (struct tlsv1_credentials*,int /*<<< orphan*/  const*,size_t,char const*) ; 
 int /*<<< orphan*/ * tlsv1_set_key_enc_pem (int /*<<< orphan*/  const*,size_t,char const*) ; 
 int /*<<< orphan*/ * tlsv1_set_key_pem (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tlsv1_set_key(struct tlsv1_credentials *cred,
			 const u8 *key, size_t len, const char *passwd)
{
	cred->key = crypto_private_key_import(key, len, passwd);
	if (cred->key == NULL)
		cred->key = tlsv1_set_key_pem(key, len);
	if (cred->key == NULL)
		cred->key = tlsv1_set_key_enc_pem(key, len, passwd);
#ifdef PKCS12_FUNCS
	if (!cred->key)
		pkcs12_parse(cred, key, len, passwd);
#endif /* PKCS12_FUNCS */
	if (cred->key == NULL) {
		wpa_printf(MSG_INFO, "TLSv1: Failed to parse private key");
		return -1;
	}
	return 0;
}