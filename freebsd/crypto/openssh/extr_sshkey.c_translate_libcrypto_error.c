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

/* Variables and functions */
 int ERR_GET_LIB (unsigned long) ; 
 int ERR_GET_REASON (unsigned long) ; 
#define  ERR_LIB_ASN1 137 
#define  ERR_LIB_EVP 136 
#define  ERR_LIB_PEM 135 
#define  EVP_R_BAD_DECRYPT 134 
#define  EVP_R_BN_DECODE_ERROR 133 
#define  EVP_R_DECODE_ERROR 132 
#define  EVP_R_PRIVATE_KEY_DECODE_ERROR 131 
#define  PEM_R_BAD_DECRYPT 130 
#define  PEM_R_BAD_PASSWORD_READ 129 
#define  PEM_R_PROBLEMS_GETTING_PASSWORD 128 
 int SSH_ERR_INVALID_FORMAT ; 
 int SSH_ERR_KEY_WRONG_PASSPHRASE ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 

__attribute__((used)) static int
translate_libcrypto_error(unsigned long pem_err)
{
	int pem_reason = ERR_GET_REASON(pem_err);

	switch (ERR_GET_LIB(pem_err)) {
	case ERR_LIB_PEM:
		switch (pem_reason) {
		case PEM_R_BAD_PASSWORD_READ:
		case PEM_R_PROBLEMS_GETTING_PASSWORD:
		case PEM_R_BAD_DECRYPT:
			return SSH_ERR_KEY_WRONG_PASSPHRASE;
		default:
			return SSH_ERR_INVALID_FORMAT;
		}
	case ERR_LIB_EVP:
		switch (pem_reason) {
		case EVP_R_BAD_DECRYPT:
			return SSH_ERR_KEY_WRONG_PASSPHRASE;
#ifdef EVP_R_BN_DECODE_ERROR
		case EVP_R_BN_DECODE_ERROR:
#endif
		case EVP_R_DECODE_ERROR:
#ifdef EVP_R_PRIVATE_KEY_DECODE_ERROR
		case EVP_R_PRIVATE_KEY_DECODE_ERROR:
#endif
			return SSH_ERR_INVALID_FORMAT;
		default:
			return SSH_ERR_LIBCRYPTO_ERROR;
		}
	case ERR_LIB_ASN1:
		return SSH_ERR_INVALID_FORMAT;
	}
	return SSH_ERR_LIBCRYPTO_ERROR;
}