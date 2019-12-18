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
typedef  int /*<<< orphan*/  u64 ;
struct md5_state {scalar_t__ hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_octeon_64bit_hash_dword (int) ; 

__attribute__((used)) static void octeon_md5_read_hash(struct md5_state *ctx)
{
	u64 *hash = (u64 *)ctx->hash;

	hash[0] = read_octeon_64bit_hash_dword(0);
	hash[1] = read_octeon_64bit_hash_dword(1);
}