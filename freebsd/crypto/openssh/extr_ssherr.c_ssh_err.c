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
#define  SSH_ERR_AGENT_COMMUNICATION 186 
#define  SSH_ERR_AGENT_FAILURE 185 
#define  SSH_ERR_AGENT_NOT_PRESENT 184 
#define  SSH_ERR_AGENT_NO_IDENTITIES 183 
#define  SSH_ERR_ALLOC_FAIL 182 
#define  SSH_ERR_BIGNUM_IS_NEGATIVE 181 
#define  SSH_ERR_BIGNUM_TOO_LARGE 180 
#define  SSH_ERR_BUFFER_READ_ONLY 179 
#define  SSH_ERR_CONN_CLOSED 178 
#define  SSH_ERR_CONN_CORRUPT 177 
#define  SSH_ERR_CONN_TIMEOUT 176 
#define  SSH_ERR_DH_GEX_OUT_OF_RANGE 175 
#define  SSH_ERR_DISCONNECTED 174 
#define  SSH_ERR_ECPOINT_TOO_LARGE 173 
#define  SSH_ERR_EC_CURVE_INVALID 172 
#define  SSH_ERR_EC_CURVE_MISMATCH 171 
#define  SSH_ERR_EXPECTED_CERT 170 
#define  SSH_ERR_FILE_CHANGED 169 
#define  SSH_ERR_INTERNAL_ERROR 168 
#define  SSH_ERR_INVALID_ARGUMENT 167 
#define  SSH_ERR_INVALID_FORMAT 166 
#define  SSH_ERR_KEY_BAD_PERMISSIONS 165 
#define  SSH_ERR_KEY_BITS_MISMATCH 164 
#define  SSH_ERR_KEY_CERT_INVALID 163 
#define  SSH_ERR_KEY_CERT_INVALID_SIGN_KEY 162 
#define  SSH_ERR_KEY_CERT_MISMATCH 161 
#define  SSH_ERR_KEY_CERT_UNKNOWN_TYPE 160 
#define  SSH_ERR_KEY_INVALID_EC_VALUE 159 
#define  SSH_ERR_KEY_LACKS_CERTBLOB 158 
#define  SSH_ERR_KEY_LENGTH 157 
#define  SSH_ERR_KEY_NOT_FOUND 156 
#define  SSH_ERR_KEY_REVOKED 155 
#define  SSH_ERR_KEY_TYPE_MISMATCH 154 
#define  SSH_ERR_KEY_TYPE_UNKNOWN 153 
#define  SSH_ERR_KEY_UNKNOWN_CIPHER 152 
#define  SSH_ERR_KEY_WRONG_PASSPHRASE 151 
#define  SSH_ERR_KRL_BAD_MAGIC 150 
#define  SSH_ERR_LIBCRYPTO_ERROR 149 
#define  SSH_ERR_MAC_INVALID 148 
#define  SSH_ERR_MESSAGE_INCOMPLETE 147 
#define  SSH_ERR_NEED_REKEY 146 
#define  SSH_ERR_NO_BUFFER_SPACE 145 
#define  SSH_ERR_NO_CIPHER_ALG_MATCH 144 
#define  SSH_ERR_NO_COMPRESS_ALG_MATCH 143 
#define  SSH_ERR_NO_HOSTKEY_ALG_MATCH 142 
#define  SSH_ERR_NO_HOSTKEY_LOADED 141 
#define  SSH_ERR_NO_KEX_ALG_MATCH 140 
#define  SSH_ERR_NO_MAC_ALG_MATCH 139 
#define  SSH_ERR_NO_PROTOCOL_VERSION 138 
#define  SSH_ERR_NUMBER_TOO_LARGE 137 
#define  SSH_ERR_PASSPHRASE_TOO_SHORT 136 
#define  SSH_ERR_PROTOCOL_ERROR 135 
#define  SSH_ERR_PROTOCOL_MISMATCH 134 
#define  SSH_ERR_SIGNATURE_INVALID 133 
#define  SSH_ERR_SIGN_ALG_UNSUPPORTED 132 
#define  SSH_ERR_STRING_TOO_LARGE 131 
#define  SSH_ERR_SUCCESS 130 
#define  SSH_ERR_SYSTEM_ERROR 129 
#define  SSH_ERR_UNEXPECTED_TRAILING_DATA 128 
 int /*<<< orphan*/  errno ; 
 char const* strerror (int /*<<< orphan*/ ) ; 

const char *
ssh_err(int n)
{
	switch (n) {
	case SSH_ERR_SUCCESS:
		return "success";
	case SSH_ERR_INTERNAL_ERROR:
		return "unexpected internal error";
	case SSH_ERR_ALLOC_FAIL:
		return "memory allocation failed";
	case SSH_ERR_MESSAGE_INCOMPLETE:
		return "incomplete message";
	case SSH_ERR_INVALID_FORMAT:
		return "invalid format";
	case SSH_ERR_BIGNUM_IS_NEGATIVE:
		return "bignum is negative";
	case SSH_ERR_STRING_TOO_LARGE:
		return "string is too large";
	case SSH_ERR_BIGNUM_TOO_LARGE:
		return "bignum is too large";
	case SSH_ERR_ECPOINT_TOO_LARGE:
		return "elliptic curve point is too large";
	case SSH_ERR_NO_BUFFER_SPACE:
		return "insufficient buffer space";
	case SSH_ERR_INVALID_ARGUMENT:
		return "invalid argument";
	case SSH_ERR_KEY_BITS_MISMATCH:
		return "key bits do not match";
	case SSH_ERR_EC_CURVE_INVALID:
		return "invalid elliptic curve";
	case SSH_ERR_KEY_TYPE_MISMATCH:
		return "key type does not match";
	case SSH_ERR_KEY_TYPE_UNKNOWN:
		return "unknown or unsupported key type";
	case SSH_ERR_EC_CURVE_MISMATCH:
		return "elliptic curve does not match";
	case SSH_ERR_EXPECTED_CERT:
		return "plain key provided where certificate required";
	case SSH_ERR_KEY_LACKS_CERTBLOB:
		return "key lacks certificate data";
	case SSH_ERR_KEY_CERT_UNKNOWN_TYPE:
		return "unknown/unsupported certificate type";
	case SSH_ERR_KEY_CERT_INVALID_SIGN_KEY:
		return "invalid certificate signing key";
	case SSH_ERR_KEY_INVALID_EC_VALUE:
		return "invalid elliptic curve value";
	case SSH_ERR_SIGNATURE_INVALID:
		return "incorrect signature";
	case SSH_ERR_LIBCRYPTO_ERROR:
		return "error in libcrypto";  /* XXX fetch and return */
	case SSH_ERR_UNEXPECTED_TRAILING_DATA:
		return "unexpected bytes remain after decoding";
	case SSH_ERR_SYSTEM_ERROR:
		return strerror(errno);
	case SSH_ERR_KEY_CERT_INVALID:
		return "invalid certificate";
	case SSH_ERR_AGENT_COMMUNICATION:
		return "communication with agent failed";
	case SSH_ERR_AGENT_FAILURE:
		return "agent refused operation";
	case SSH_ERR_DH_GEX_OUT_OF_RANGE:
		return "DH GEX group out of range";
	case SSH_ERR_DISCONNECTED:
		return "disconnected";
	case SSH_ERR_MAC_INVALID:
		return "message authentication code incorrect";
	case SSH_ERR_NO_CIPHER_ALG_MATCH:
		return "no matching cipher found";
	case SSH_ERR_NO_MAC_ALG_MATCH:
		return "no matching MAC found";
	case SSH_ERR_NO_COMPRESS_ALG_MATCH:
		return "no matching compression method found";
	case SSH_ERR_NO_KEX_ALG_MATCH:
		return "no matching key exchange method found";
	case SSH_ERR_NO_HOSTKEY_ALG_MATCH:
		return "no matching host key type found";
	case SSH_ERR_PROTOCOL_MISMATCH:
		return "protocol version mismatch";
	case SSH_ERR_NO_PROTOCOL_VERSION:
		return "could not read protocol version";
	case SSH_ERR_NO_HOSTKEY_LOADED:
		return "could not load host key";
	case SSH_ERR_NEED_REKEY:
		return "rekeying not supported by peer";
	case SSH_ERR_PASSPHRASE_TOO_SHORT:
		return "passphrase is too short (minimum five characters)";
	case SSH_ERR_FILE_CHANGED:
		return "file changed while reading";
	case SSH_ERR_KEY_UNKNOWN_CIPHER:
		return "key encrypted using unsupported cipher";
	case SSH_ERR_KEY_WRONG_PASSPHRASE:
		return "incorrect passphrase supplied to decrypt private key";
	case SSH_ERR_KEY_BAD_PERMISSIONS:
		return "bad permissions";
	case SSH_ERR_KEY_CERT_MISMATCH:
		return "certificate does not match key";
	case SSH_ERR_KEY_NOT_FOUND:
		return "key not found";
	case SSH_ERR_AGENT_NOT_PRESENT:
		return "agent not present";
	case SSH_ERR_AGENT_NO_IDENTITIES:
		return "agent contains no identities";
	case SSH_ERR_BUFFER_READ_ONLY:
		return "internal error: buffer is read-only";
	case SSH_ERR_KRL_BAD_MAGIC:
		return "KRL file has invalid magic number";
	case SSH_ERR_KEY_REVOKED:
		return "Key is revoked";
	case SSH_ERR_CONN_CLOSED:
		return "Connection closed";
	case SSH_ERR_CONN_TIMEOUT:
		return "Connection timed out";
	case SSH_ERR_CONN_CORRUPT:
		return "Connection corrupted";
	case SSH_ERR_PROTOCOL_ERROR:
		return "Protocol error";
	case SSH_ERR_KEY_LENGTH:
		return "Invalid key length";
	case SSH_ERR_NUMBER_TOO_LARGE:
		return "number is too large";
	case SSH_ERR_SIGN_ALG_UNSUPPORTED:
		return "signature algorithm not supported";
	default:
		return "unknown error";
	}
}