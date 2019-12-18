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
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  const* EVP_md5 () ; 
 int /*<<< orphan*/  const* EVP_sha1 () ; 
 int /*<<< orphan*/  const* EVP_sha256 () ; 
 int /*<<< orphan*/  const* EVP_sha384 () ; 
 int /*<<< orphan*/  const* EVP_sha512 () ; 
 scalar_t__ strcasecmp (char*,char*) ; 

__attribute__((used)) static const EVP_MD *
ldns_digest_function(char *name)
{
	/* these are the mandatory algorithms from RFC4635 */
	/* The optional algorithms are not yet implemented */
	if (strcasecmp(name, "hmac-sha512.") == 0) {
#ifdef HAVE_EVP_SHA512
		return EVP_sha512();
#else
		return NULL;
#endif
	} else if (strcasecmp(name, "hmac-shac384.") == 0) {
#ifdef HAVE_EVP_SHA384
		return EVP_sha384();
#else
		return NULL;
#endif
	} else if (strcasecmp(name, "hmac-sha256.") == 0) {
#ifdef HAVE_EVP_SHA256
		return EVP_sha256();
#else
		return NULL;
#endif
	} else if (strcasecmp(name, "hmac-sha1.") == 0) {
		return EVP_sha1();
	} else if (strcasecmp(name, "hmac-md5.sig-alg.reg.int.") == 0) {
		return EVP_md5();
	} else {
		return NULL;
	}
}