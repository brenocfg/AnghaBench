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
typedef  int /*<<< orphan*/  id ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 size_t CHAP_DIGEST_LEN ; 
 int /*<<< orphan*/  MD5Final (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
chap_compute_md5(const char id, const char *secret,
    const void *challenge, size_t challenge_len, void *response,
    size_t response_len)
{
	MD5_CTX ctx;

	assert(response_len == CHAP_DIGEST_LEN);

	MD5Init(&ctx);
	MD5Update(&ctx, &id, sizeof(id));
	MD5Update(&ctx, secret, strlen(secret));
	MD5Update(&ctx, challenge, challenge_len);
	MD5Final(response, &ctx);
}