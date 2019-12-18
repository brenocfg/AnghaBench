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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
#define  SHA1_DIGEST_SIZE 132 
 size_t SHA1_INIT_STATE ; 
#define  SHA224_DIGEST_SIZE 131 
 size_t SHA224_INIT_STATE ; 
#define  SHA256_DIGEST_SIZE 130 
 size_t SHA256_INIT_STATE ; 
#define  SHA384_DIGEST_SIZE 129 
 size_t SHA384_INIT_STATE ; 
#define  SHA512_DIGEST_SIZE 128 
 size_t SHA512_INIT_STATE ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * chcr_sha1_init ; 
 int /*<<< orphan*/ * chcr_sha224_init ; 
 int /*<<< orphan*/ * chcr_sha256_init ; 
 scalar_t__ chcr_sha384_init ; 
 scalar_t__ chcr_sha512_init ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void copy_hash_init_values(char *key, int digestsize)
{
	u8 i;
	__be32 *dkey = (__be32 *)key;
	u64 *ldkey = (u64 *)key;
	__be64 *sha384 = (__be64 *)chcr_sha384_init;
	__be64 *sha512 = (__be64 *)chcr_sha512_init;

	switch (digestsize) {
	case SHA1_DIGEST_SIZE:
		for (i = 0; i < SHA1_INIT_STATE; i++)
			dkey[i] = cpu_to_be32(chcr_sha1_init[i]);
		break;
	case SHA224_DIGEST_SIZE:
		for (i = 0; i < SHA224_INIT_STATE; i++)
			dkey[i] = cpu_to_be32(chcr_sha224_init[i]);
		break;
	case SHA256_DIGEST_SIZE:
		for (i = 0; i < SHA256_INIT_STATE; i++)
			dkey[i] = cpu_to_be32(chcr_sha256_init[i]);
		break;
	case SHA384_DIGEST_SIZE:
		for (i = 0; i < SHA384_INIT_STATE; i++)
			ldkey[i] = be64_to_cpu(sha384[i]);
		break;
	case SHA512_DIGEST_SIZE:
		for (i = 0; i < SHA512_INIT_STATE; i++)
			ldkey[i] = be64_to_cpu(sha512[i]);
		break;
	}
}