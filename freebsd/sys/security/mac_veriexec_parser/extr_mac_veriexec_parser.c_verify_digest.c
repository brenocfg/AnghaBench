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
 int SHA256_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SHA256_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_Update (int /*<<< orphan*/ *,char const*,size_t) ; 
 int memcmp (unsigned char const*,unsigned char*,int) ; 

__attribute__((used)) static int
verify_digest(const char *data, size_t len, const unsigned char *expected_hash)
{
	SHA256_CTX	ctx;
	unsigned char	hash[SHA256_DIGEST_LENGTH];

	SHA256_Init(&ctx);
	SHA256_Update(&ctx, data, len);
	SHA256_Final(hash, &ctx);

	return (memcmp(expected_hash, hash, SHA256_DIGEST_LENGTH));
}