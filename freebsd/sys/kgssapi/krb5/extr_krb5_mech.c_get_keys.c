#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {int* kd_data; } ;
struct krb5_keyblock {int kk_type; TYPE_1__ kk_key; } ;
struct krb5_key_state {int* ks_key; int /*<<< orphan*/  ks_refs; } ;
struct krb5_encryption_class {int ec_keylen; } ;
struct krb5_context {int kc_more_flags; void* kc_recv_sign_Kc; void* kc_recv_seal_Kc; void* kc_recv_seal_Ki; void* kc_recv_seal_Ke; void* kc_send_sign_Kc; void* kc_send_seal_Kc; void* kc_send_seal_Ki; void* kc_send_seal_Ke; struct krb5_key_state* kc_encryptkey; struct krb5_key_state* kc_checksumkey; struct krb5_key_state* kc_tokenkey; } ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int ACCEPTOR_SUBKEY ; 
#define  ETYPE_ARCFOUR_HMAC_MD5 135 
#define  ETYPE_ARCFOUR_HMAC_MD5_56 134 
#define  ETYPE_DES3_CBC_MD5 133 
#define  ETYPE_DES3_CBC_SHA1 132 
#define  ETYPE_DES_CBC_CRC 131 
#define  ETYPE_DES_CBC_MD4 130 
#define  ETYPE_DES_CBC_MD5 129 
#define  ETYPE_OLD_DES3_CBC_SHA1 128 
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 int /*<<< orphan*/  GSS_S_FAILURE ; 
 int /*<<< orphan*/  KG_USAGE_ACCEPTOR_SEAL ; 
 int /*<<< orphan*/  KG_USAGE_ACCEPTOR_SIGN ; 
 int /*<<< orphan*/  KG_USAGE_INITIATOR_SEAL ; 
 int /*<<< orphan*/  KG_USAGE_INITIATOR_SIGN ; 
 int /*<<< orphan*/  KG_USAGE_SIGN ; 
 int /*<<< orphan*/  get_acceptor_subkey (struct krb5_context*,struct krb5_keyblock**) ; 
 int /*<<< orphan*/  get_initiator_subkey (struct krb5_context*,struct krb5_keyblock**) ; 
 int /*<<< orphan*/  is_initiator (struct krb5_context*) ; 
 struct krb5_key_state* krb5_create_key (struct krb5_encryption_class*) ; 
 struct krb5_encryption_class* krb5_find_encryption_class (int) ; 
 void* krb5_get_checksum_key (struct krb5_key_state*,int /*<<< orphan*/ ) ; 
 void* krb5_get_encryption_key (struct krb5_key_state*,int /*<<< orphan*/ ) ; 
 void* krb5_get_integrity_key (struct krb5_key_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_set_key (struct krb5_key_state*,int*) ; 
 int /*<<< orphan*/  refcount_acquire (int /*<<< orphan*/ *) ; 

__attribute__((used)) static OM_uint32
get_keys(struct krb5_context *kc)
{
	struct krb5_keyblock *keydata;
	struct krb5_encryption_class *ec;
	struct krb5_key_state *key;
	int etype;

	keydata = NULL;
	get_acceptor_subkey(kc, &keydata);
	if (!keydata)
		if ((kc->kc_more_flags & ACCEPTOR_SUBKEY) == 0)
			get_initiator_subkey(kc, &keydata);
	if (!keydata)
		return (GSS_S_FAILURE);

	/*
	 * GSS-API treats all DES etypes the same and all DES3 etypes
	 * the same.
	 */
	switch (keydata->kk_type) {
	case ETYPE_DES_CBC_CRC:
	case ETYPE_DES_CBC_MD4:
	case ETYPE_DES_CBC_MD5:
		etype = ETYPE_DES_CBC_CRC;
		break;

	case ETYPE_DES3_CBC_MD5:
	case ETYPE_DES3_CBC_SHA1:
	case ETYPE_OLD_DES3_CBC_SHA1:
		etype = ETYPE_DES3_CBC_SHA1;
		break;

	default:
		etype = keydata->kk_type;
	}

	ec = krb5_find_encryption_class(etype);
	if (!ec)
		return (GSS_S_FAILURE);

	key = krb5_create_key(ec);
	krb5_set_key(key, keydata->kk_key.kd_data);
	kc->kc_tokenkey = key;

	switch (etype) {
	case ETYPE_DES_CBC_CRC:
	case ETYPE_ARCFOUR_HMAC_MD5: 
	case ETYPE_ARCFOUR_HMAC_MD5_56: {
		/*
		 * Single DES and ARCFOUR uses a 'derived' key (XOR
		 * with 0xf0) for encrypting wrap tokens. The original
		 * key is used for checksums and sequence numbers.
		 */
		struct krb5_key_state *ekey;
		uint8_t *ekp, *kp;
		int i;

		ekey = krb5_create_key(ec);
		ekp = ekey->ks_key;
		kp = key->ks_key;
		for (i = 0; i < ec->ec_keylen; i++)
			ekp[i] = kp[i] ^ 0xf0;
		krb5_set_key(ekey, ekp);
		kc->kc_encryptkey = ekey;
		refcount_acquire(&key->ks_refs);
		kc->kc_checksumkey = key;
		break;
	}

	case ETYPE_DES3_CBC_SHA1:
		/*
		 * Triple DES uses a RFC 3961 style derived key with
		 * usage number KG_USAGE_SIGN for checksums. The
		 * original key is used for encryption and sequence
		 * numbers.
		 */
		kc->kc_checksumkey = krb5_get_checksum_key(key, KG_USAGE_SIGN);
		refcount_acquire(&key->ks_refs);
		kc->kc_encryptkey = key;
		break;

	default:
		/*
		 * We need eight derived keys four for sending and
		 * four for receiving.
		 */
		if (is_initiator(kc)) {
			/*
			 * We are initiator.
			 */
			kc->kc_send_seal_Ke = krb5_get_encryption_key(key,
			    KG_USAGE_INITIATOR_SEAL);
			kc->kc_send_seal_Ki = krb5_get_integrity_key(key,
			    KG_USAGE_INITIATOR_SEAL);
			kc->kc_send_seal_Kc = krb5_get_checksum_key(key,
			    KG_USAGE_INITIATOR_SEAL);
			kc->kc_send_sign_Kc = krb5_get_checksum_key(key,
			    KG_USAGE_INITIATOR_SIGN);

			kc->kc_recv_seal_Ke = krb5_get_encryption_key(key,
			    KG_USAGE_ACCEPTOR_SEAL);
			kc->kc_recv_seal_Ki = krb5_get_integrity_key(key,
			    KG_USAGE_ACCEPTOR_SEAL);
			kc->kc_recv_seal_Kc = krb5_get_checksum_key(key,
			    KG_USAGE_ACCEPTOR_SEAL);
			kc->kc_recv_sign_Kc = krb5_get_checksum_key(key,
			    KG_USAGE_ACCEPTOR_SIGN);
		} else {
			/*
			 * We are acceptor.
			 */
			kc->kc_send_seal_Ke = krb5_get_encryption_key(key,
			    KG_USAGE_ACCEPTOR_SEAL);
			kc->kc_send_seal_Ki = krb5_get_integrity_key(key,
			    KG_USAGE_ACCEPTOR_SEAL);
			kc->kc_send_seal_Kc = krb5_get_checksum_key(key,
			    KG_USAGE_ACCEPTOR_SEAL);
			kc->kc_send_sign_Kc = krb5_get_checksum_key(key,
			    KG_USAGE_ACCEPTOR_SIGN);

			kc->kc_recv_seal_Ke = krb5_get_encryption_key(key,
			    KG_USAGE_INITIATOR_SEAL);
			kc->kc_recv_seal_Ki = krb5_get_integrity_key(key,
			    KG_USAGE_INITIATOR_SEAL);
			kc->kc_recv_seal_Kc = krb5_get_checksum_key(key,
			    KG_USAGE_INITIATOR_SEAL);
			kc->kc_recv_sign_Kc = krb5_get_checksum_key(key,
			    KG_USAGE_INITIATOR_SIGN);
		}
		break;
	}

	return (GSS_S_COMPLETE);
}