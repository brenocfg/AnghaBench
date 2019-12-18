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
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
#define  EVP_PKEY_DH 131 
#define  EVP_PKEY_DSA 130 
#define  EVP_PKEY_EC 129 
#define  EVP_PKEY_RSA 128 
 int /*<<< orphan*/  EVP_PKEY_id (int /*<<< orphan*/  const*) ; 
 int EVP_PKEY_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char * openssl_pkey_type_str(const EVP_PKEY *pkey)
{
	if (!pkey)
		return "NULL";
	switch (EVP_PKEY_type(EVP_PKEY_id(pkey))) {
	case EVP_PKEY_RSA:
		return "RSA";
	case EVP_PKEY_DSA:
		return "DSA";
	case EVP_PKEY_DH:
		return "DH";
	case EVP_PKEY_EC:
		return "EC";
	}
	return "?";
}