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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp1 ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,char const*,size_t,size_t) ; 
 int EVP_MAX_MD_SIZE ; 
 void const* EVP_md2 () ; 
 void const* EVP_md4 () ; 
 void const* EVP_md5 () ; 
 void const* EVP_ripemd160 () ; 
 void const* EVP_sha1 () ; 
 void const* EVP_sha224 () ; 
 void const* EVP_sha256 () ; 
 void const* EVP_sha384 () ; 
 void const* EVP_sha512 () ; 
 void* HMAC (void const*,size_t*,size_t,size_t*,size_t,size_t*,unsigned int*) ; 
 size_t __arraycount (char const**) ; 
 size_t hmac (char const*,size_t*,size_t,size_t*,size_t,size_t*,int) ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
test(void)
{
	uint8_t         tmp1[EVP_MAX_MD_SIZE];
	uint8_t         tmp2[EVP_MAX_MD_SIZE];
	uint8_t key[256];
	uint8_t data[4096];
	unsigned int tmp1len;
	size_t tmp2len;
	int stop;
	void *e1;
	const void *evps[] = {
		EVP_md2(),
		EVP_md4(),
		EVP_md5(),
		EVP_ripemd160(),
		EVP_sha1(),
		EVP_sha224(),
		EVP_sha256(),
		EVP_sha384(),
		EVP_sha512(),
	};
	const char *names[] = {
		"md2",
		"md4",
		"md5",
		"rmd160",
		"sha1",
		"sha224",
		"sha256",
		"sha384",
		"sha512",
	};

	for (size_t k = 0; k < sizeof(key); k++)
		key[k] = k;
	for (size_t d = 0; d < sizeof(data); d++)
		data[d] = d % 256;

	for (size_t t = 0; t < __arraycount(names); t++)
	    for (size_t i = 1; i < sizeof(key); i += 9)
		for (size_t j = 3; j < sizeof(data); j += 111) {
			stop = 0;
#ifdef DEBUG
			printf("%s: keysize = %zu datasize = %zu\n", names[t],
			    i, j);
#endif
			memset(tmp1, 0, sizeof(tmp1));
			memset(tmp2, 0, sizeof(tmp2));
			e1 = HMAC(evps[t], key, i, data, j, tmp1, &tmp1len);
			ATF_REQUIRE(e1 != NULL);
			tmp2len = hmac(names[t], key, i, data, j, tmp2,
			    sizeof(tmp2));
			ATF_REQUIRE_MSG(tmp1len == tmp2len, "hash %s len %u "
			    "!= %zu", names[t], tmp1len, tmp2len);
			for (size_t k = 0; k < tmp2len; k++)
				if (tmp1[k] != tmp2[k]) {
#ifdef DEBUG
					printf("%zu %.2x %.2x\n",
					    k, tmp1[k], tmp2[k]);
#endif
					stop = 1;
					break;
				}
			ATF_REQUIRE_MSG(!stop, "hash %s failed for "
				"keylen=%zu, datalen=%zu", names[t], i, j);
		}
}