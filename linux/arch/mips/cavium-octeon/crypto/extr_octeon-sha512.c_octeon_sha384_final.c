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
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memzero_explicit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  octeon_sha512_final (struct shash_desc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int octeon_sha384_final(struct shash_desc *desc, u8 *hash)
{
	u8 D[64];

	octeon_sha512_final(desc, D);

	memcpy(hash, D, 48);
	memzero_explicit(D, 64);

	return 0;
}