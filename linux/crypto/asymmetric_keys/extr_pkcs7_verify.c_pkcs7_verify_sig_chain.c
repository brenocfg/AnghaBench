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
struct x509_certificate {int seen; int blacklisted; struct x509_certificate* signer; struct public_key_signature* sig; int /*<<< orphan*/  pub; int /*<<< orphan*/  subject; int /*<<< orphan*/  index; TYPE_1__* skid; struct x509_certificate* next; TYPE_1__* id; scalar_t__ unsupported_sig; scalar_t__ self_signed; int /*<<< orphan*/  issuer; scalar_t__ unsupported_key; int /*<<< orphan*/  raw_serial; int /*<<< orphan*/  raw_serial_size; } ;
struct public_key_signature {struct asymmetric_key_id** auth_ids; } ;
struct pkcs7_signed_info {int blacklisted; int /*<<< orphan*/  index; struct x509_certificate* signer; } ;
struct pkcs7_message {struct x509_certificate* certs; } ;
struct asymmetric_key_id {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int EKEYREJECTED ; 
 scalar_t__ asymmetric_key_id_same (TYPE_1__*,struct asymmetric_key_id*) ; 
 int /*<<< orphan*/  kenter (char*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,...) ; 
 int public_key_verify_signature (int /*<<< orphan*/ ,struct public_key_signature*) ; 

__attribute__((used)) static int pkcs7_verify_sig_chain(struct pkcs7_message *pkcs7,
				  struct pkcs7_signed_info *sinfo)
{
	struct public_key_signature *sig;
	struct x509_certificate *x509 = sinfo->signer, *p;
	struct asymmetric_key_id *auth;
	int ret;

	kenter("");

	for (p = pkcs7->certs; p; p = p->next)
		p->seen = false;

	for (;;) {
		pr_debug("verify %s: %*phN\n",
			 x509->subject,
			 x509->raw_serial_size, x509->raw_serial);
		x509->seen = true;

		if (x509->blacklisted) {
			/* If this cert is blacklisted, then mark everything
			 * that depends on this as blacklisted too.
			 */
			sinfo->blacklisted = true;
			for (p = sinfo->signer; p != x509; p = p->signer)
				p->blacklisted = true;
			pr_debug("- blacklisted\n");
			return 0;
		}

		if (x509->unsupported_key)
			goto unsupported_crypto_in_x509;

		pr_debug("- issuer %s\n", x509->issuer);
		sig = x509->sig;
		if (sig->auth_ids[0])
			pr_debug("- authkeyid.id %*phN\n",
				 sig->auth_ids[0]->len, sig->auth_ids[0]->data);
		if (sig->auth_ids[1])
			pr_debug("- authkeyid.skid %*phN\n",
				 sig->auth_ids[1]->len, sig->auth_ids[1]->data);

		if (x509->self_signed) {
			/* If there's no authority certificate specified, then
			 * the certificate must be self-signed and is the root
			 * of the chain.  Likewise if the cert is its own
			 * authority.
			 */
			if (x509->unsupported_sig)
				goto unsupported_crypto_in_x509;
			x509->signer = x509;
			pr_debug("- self-signed\n");
			return 0;
		}

		/* Look through the X.509 certificates in the PKCS#7 message's
		 * list to see if the next one is there.
		 */
		auth = sig->auth_ids[0];
		if (auth) {
			pr_debug("- want %*phN\n", auth->len, auth->data);
			for (p = pkcs7->certs; p; p = p->next) {
				pr_debug("- cmp [%u] %*phN\n",
					 p->index, p->id->len, p->id->data);
				if (asymmetric_key_id_same(p->id, auth))
					goto found_issuer_check_skid;
			}
		} else if (sig->auth_ids[1]) {
			auth = sig->auth_ids[1];
			pr_debug("- want %*phN\n", auth->len, auth->data);
			for (p = pkcs7->certs; p; p = p->next) {
				if (!p->skid)
					continue;
				pr_debug("- cmp [%u] %*phN\n",
					 p->index, p->skid->len, p->skid->data);
				if (asymmetric_key_id_same(p->skid, auth))
					goto found_issuer;
			}
		}

		/* We didn't find the root of this chain */
		pr_debug("- top\n");
		return 0;

	found_issuer_check_skid:
		/* We matched issuer + serialNumber, but if there's an
		 * authKeyId.keyId, that must match the CA subjKeyId also.
		 */
		if (sig->auth_ids[1] &&
		    !asymmetric_key_id_same(p->skid, sig->auth_ids[1])) {
			pr_warn("Sig %u: X.509 chain contains auth-skid nonmatch (%u->%u)\n",
				sinfo->index, x509->index, p->index);
			return -EKEYREJECTED;
		}
	found_issuer:
		pr_debug("- subject %s\n", p->subject);
		if (p->seen) {
			pr_warn("Sig %u: X.509 chain contains loop\n",
				sinfo->index);
			return 0;
		}
		ret = public_key_verify_signature(p->pub, x509->sig);
		if (ret < 0)
			return ret;
		x509->signer = p;
		if (x509 == p) {
			pr_debug("- self-signed\n");
			return 0;
		}
		x509 = p;
		might_sleep();
	}

unsupported_crypto_in_x509:
	/* Just prune the certificate chain at this point if we lack some
	 * crypto module to go further.  Note, however, we don't want to set
	 * sinfo->unsupported_crypto as the signed info block may still be
	 * validatable against an X.509 cert lower in the chain that we have a
	 * trusted copy of.
	 */
	return 0;
}