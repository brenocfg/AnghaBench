#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct x509_certificate {TYPE_1__* pub; int /*<<< orphan*/  id; struct x509_certificate* next; } ;
struct pkcs7_signed_info {TYPE_2__* sig; int /*<<< orphan*/  index; struct x509_certificate* signer; } ;
struct pkcs7_message {struct x509_certificate* certs; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct TYPE_5__ {TYPE_3__** auth_ids; int /*<<< orphan*/  pkey_algo; } ;
struct TYPE_4__ {int /*<<< orphan*/  pkey_algo; } ;

/* Variables and functions */
 int /*<<< orphan*/  asymmetric_key_id_same (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pkcs7_find_key(struct pkcs7_message *pkcs7,
			  struct pkcs7_signed_info *sinfo)
{
	struct x509_certificate *x509;
	unsigned certix = 1;

	kenter("%u", sinfo->index);

	for (x509 = pkcs7->certs; x509; x509 = x509->next, certix++) {
		/* I'm _assuming_ that the generator of the PKCS#7 message will
		 * encode the fields from the X.509 cert in the same way in the
		 * PKCS#7 message - but I can't be 100% sure of that.  It's
		 * possible this will need element-by-element comparison.
		 */
		if (!asymmetric_key_id_same(x509->id, sinfo->sig->auth_ids[0]))
			continue;
		pr_devel("Sig %u: Found cert serial match X.509[%u]\n",
			 sinfo->index, certix);

		if (strcmp(x509->pub->pkey_algo, sinfo->sig->pkey_algo) != 0) {
			pr_warn("Sig %u: X.509 algo and PKCS#7 sig algo don't match\n",
				sinfo->index);
			continue;
		}

		sinfo->signer = x509;
		return 0;
	}

	/* The relevant X.509 cert isn't found here, but it might be found in
	 * the trust keyring.
	 */
	pr_debug("Sig %u: Issuing X.509 cert not found (#%*phN)\n",
		 sinfo->index,
		 sinfo->sig->auth_ids[0]->len, sinfo->sig->auth_ids[0]->data);
	return 0;
}