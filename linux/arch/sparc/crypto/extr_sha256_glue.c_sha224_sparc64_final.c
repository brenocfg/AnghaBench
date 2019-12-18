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
typedef  int /*<<< orphan*/  u8 ;
struct shash_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHA224_DIGEST_SIZE ; 
 int SHA256_DIGEST_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memzero_explicit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sha256_sparc64_final (struct shash_desc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sha224_sparc64_final(struct shash_desc *desc, u8 *hash)
{
	u8 D[SHA256_DIGEST_SIZE];

	sha256_sparc64_final(desc, D);

	memcpy(hash, D, SHA224_DIGEST_SIZE);
	memzero_explicit(D, SHA256_DIGEST_SIZE);

	return 0;
}