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
typedef  int /*<<< orphan*/  SHA256_CTX ;

/* Variables and functions */
 size_t SHA256_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SHA256_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_Update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

__attribute__((used)) static void
hast_sha256_checksum(const unsigned char *data, size_t size,
    unsigned char *hash, size_t *hsizep)
{
	SHA256_CTX ctx;

	SHA256_Init(&ctx);
	SHA256_Update(&ctx, data, size);
	SHA256_Final(hash, &ctx);
	*hsizep = SHA256_DIGEST_LENGTH;
}