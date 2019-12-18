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
 int /*<<< orphan*/  SHA256_Update (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  sha256_hash (unsigned char*,char*) ; 

__attribute__((used)) static void
sha256_buf(char *buf, size_t len, char out[SHA256_DIGEST_LENGTH * 2 + 1])
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;

	out[0] = '\0';

	SHA256_Init(&sha256);
	SHA256_Update(&sha256, buf, len);
	SHA256_Final(hash, &sha256);
	sha256_hash(hash, out);
}