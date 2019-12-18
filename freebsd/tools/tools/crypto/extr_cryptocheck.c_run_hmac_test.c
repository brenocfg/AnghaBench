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
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  test_digest ;
struct alg {char* name; int /*<<< orphan*/ * (* evp_md ) () ;} ;
typedef  int /*<<< orphan*/  control_digest ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 int EVP_MAX_MD_SIZE ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * HMAC (int /*<<< orphan*/  const*,char*,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t*) ; 
 char* alloc_buffer (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 char* crfind (int) ; 
 int /*<<< orphan*/  errx (int,char*,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hexdump (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  ocf_hmac (struct alg*,char*,size_t,char*,size_t,char*,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ * stub1 () ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
run_hmac_test(struct alg *alg, size_t size)
{
	const EVP_MD *md;
	char *key, *buffer;
	u_int key_len, digest_len;
	int crid;
	char control_digest[EVP_MAX_MD_SIZE], test_digest[EVP_MAX_MD_SIZE];

	memset(control_digest, 0x3c, sizeof(control_digest));
	memset(test_digest, 0x3c, sizeof(test_digest));

	md = alg->evp_md();
	key_len = EVP_MD_size(md);
	assert(EVP_MD_size(md) <= sizeof(control_digest));

	key = alloc_buffer(key_len);
	buffer = alloc_buffer(size);

	/* OpenSSL HMAC. */
	digest_len = sizeof(control_digest);
	if (HMAC(md, key, key_len, (u_char *)buffer, size,
	    (u_char *)control_digest, &digest_len) == NULL)
		errx(1, "OpenSSL %s (%zu) HMAC failed: %s", alg->name,
		    size, ERR_error_string(ERR_get_error(), NULL));

	/* cryptodev HMAC. */
	if (!ocf_hmac(alg, buffer, size, key, key_len, test_digest, &crid))
		goto out;
	if (memcmp(control_digest, test_digest, sizeof(control_digest)) != 0) {
		if (memcmp(control_digest, test_digest, EVP_MD_size(md)) == 0)
			printf("%s (%zu) mismatch in trailer:\n",
			    alg->name, size);
		else
			printf("%s (%zu) mismatch:\n", alg->name, size);
		printf("control:\n");
		hexdump(control_digest, sizeof(control_digest), NULL, 0);
		printf("test (cryptodev device %s):\n", crfind(crid));
		hexdump(test_digest, sizeof(test_digest), NULL, 0);
		goto out;
	}

	if (verbose)
		printf("%s (%zu) matched (cryptodev device %s)\n",
		    alg->name, size, crfind(crid));

out:
	free(buffer);
	free(key);
}