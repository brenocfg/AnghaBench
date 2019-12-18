#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {scalar_t__ type; } ;
struct crypto_private_key {TYPE_1__ rsa; } ;

/* Variables and functions */
 int CRYPT_OK ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ PK_PRIVATE ; 
 int /*<<< orphan*/  error_to_string (int) ; 
 int /*<<< orphan*/  os_free (struct crypto_private_key*) ; 
 struct crypto_private_key* os_zalloc (int) ; 
 int /*<<< orphan*/  rsa_free (TYPE_1__*) ; 
 int rsa_import (int /*<<< orphan*/  const*,size_t,TYPE_1__*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

struct crypto_private_key * crypto_private_key_import(const u8 *key,
						      size_t len,
						      const char *passwd)
{
	int res;
	struct crypto_private_key *pk;

	pk = os_zalloc(sizeof(*pk));
	if (pk == NULL)
		return NULL;

	res = rsa_import(key, len, &pk->rsa);
	if (res != CRYPT_OK) {
		wpa_printf(MSG_ERROR, "LibTomCrypt: Failed to import "
			   "private key (res=%d '%s')",
			   res, error_to_string(res));
		os_free(pk);
		return NULL;
	}

	if (pk->rsa.type != PK_PRIVATE) {
		wpa_printf(MSG_ERROR, "LibTomCrypt: Private key was not of "
			   "correct type");
		rsa_free(&pk->rsa);
		os_free(pk);
		return NULL;
	}

	return pk;
}