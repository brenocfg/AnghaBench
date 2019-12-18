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
struct x509_certificate {int seen; int verified; struct x509_certificate* signer; int /*<<< orphan*/  index; struct public_key_signature* sig; int /*<<< orphan*/ * skid; int /*<<< orphan*/ * id; } ;
struct public_key_signature {int /*<<< orphan*/ ** auth_ids; } ;
struct pkcs7_signed_info {struct x509_certificate* signer; struct public_key_signature* sig; int /*<<< orphan*/  index; scalar_t__ unsupported_crypto; } ;
struct pkcs7_message {int dummy; } ;
struct key {int dummy; } ;

/* Variables and functions */
 int EKEYREJECTED ; 
 int ENOKEY ; 
 int ENOMEM ; 
 int ENOPKG ; 
 struct key* ERR_PTR (int) ; 
 int /*<<< orphan*/  IS_ERR (struct key*) ; 
 int PTR_ERR (struct key*) ; 
 struct key* find_asymmetric_key (struct key*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 
 int /*<<< orphan*/  kleave (char*,...) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int verify_signature (struct key*,struct public_key_signature*) ; 

__attribute__((used)) static int pkcs7_validate_trust_one(struct pkcs7_message *pkcs7,
				    struct pkcs7_signed_info *sinfo,
				    struct key *trust_keyring)
{
	struct public_key_signature *sig = sinfo->sig;
	struct x509_certificate *x509, *last = NULL, *p;
	struct key *key;
	int ret;

	kenter(",%u,", sinfo->index);

	if (sinfo->unsupported_crypto) {
		kleave(" = -ENOPKG [cached]");
		return -ENOPKG;
	}

	for (x509 = sinfo->signer; x509; x509 = x509->signer) {
		if (x509->seen) {
			if (x509->verified)
				goto verified;
			kleave(" = -ENOKEY [cached]");
			return -ENOKEY;
		}
		x509->seen = true;

		/* Look to see if this certificate is present in the trusted
		 * keys.
		 */
		key = find_asymmetric_key(trust_keyring,
					  x509->id, x509->skid, false);
		if (!IS_ERR(key)) {
			/* One of the X.509 certificates in the PKCS#7 message
			 * is apparently the same as one we already trust.
			 * Verify that the trusted variant can also validate
			 * the signature on the descendant.
			 */
			pr_devel("sinfo %u: Cert %u as key %x\n",
				 sinfo->index, x509->index, key_serial(key));
			goto matched;
		}
		if (key == ERR_PTR(-ENOMEM))
			return -ENOMEM;

		 /* Self-signed certificates form roots of their own, and if we
		  * don't know them, then we can't accept them.
		  */
		if (x509->signer == x509) {
			kleave(" = -ENOKEY [unknown self-signed]");
			return -ENOKEY;
		}

		might_sleep();
		last = x509;
		sig = last->sig;
	}

	/* No match - see if the root certificate has a signer amongst the
	 * trusted keys.
	 */
	if (last && (last->sig->auth_ids[0] || last->sig->auth_ids[1])) {
		key = find_asymmetric_key(trust_keyring,
					  last->sig->auth_ids[0],
					  last->sig->auth_ids[1],
					  false);
		if (!IS_ERR(key)) {
			x509 = last;
			pr_devel("sinfo %u: Root cert %u signer is key %x\n",
				 sinfo->index, x509->index, key_serial(key));
			goto matched;
		}
		if (PTR_ERR(key) != -ENOKEY)
			return PTR_ERR(key);
	}

	/* As a last resort, see if we have a trusted public key that matches
	 * the signed info directly.
	 */
	key = find_asymmetric_key(trust_keyring,
				  sinfo->sig->auth_ids[0], NULL, false);
	if (!IS_ERR(key)) {
		pr_devel("sinfo %u: Direct signer is key %x\n",
			 sinfo->index, key_serial(key));
		x509 = NULL;
		sig = sinfo->sig;
		goto matched;
	}
	if (PTR_ERR(key) != -ENOKEY)
		return PTR_ERR(key);

	kleave(" = -ENOKEY [no backref]");
	return -ENOKEY;

matched:
	ret = verify_signature(key, sig);
	key_put(key);
	if (ret < 0) {
		if (ret == -ENOMEM)
			return ret;
		kleave(" = -EKEYREJECTED [verify %d]", ret);
		return -EKEYREJECTED;
	}

verified:
	if (x509) {
		x509->verified = true;
		for (p = sinfo->signer; p != x509; p = p->signer)
			p->verified = true;
	}
	kleave(" = 0");
	return 0;
}