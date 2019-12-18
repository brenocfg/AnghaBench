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
typedef  int /*<<< orphan*/  u32 ;
struct cword {int dummy; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  MAX_ECB_FETCH_BLOCKS ; 
 int PADLOCK_ALIGNMENT ; 
 int /*<<< orphan*/ * PTR_ALIGN (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  rep_xcrypt_ecb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cword*,int) ; 

__attribute__((used)) static void ecb_crypt_copy(const u8 *in, u8 *out, u32 *key,
			   struct cword *cword, int count)
{
	/*
	 * Padlock prefetches extra data so we must provide mapped input buffers.
	 * Assume there are at least 16 bytes of stack already in use.
	 */
	u8 buf[AES_BLOCK_SIZE * (MAX_ECB_FETCH_BLOCKS - 1) + PADLOCK_ALIGNMENT - 1];
	u8 *tmp = PTR_ALIGN(&buf[0], PADLOCK_ALIGNMENT);

	memcpy(tmp, in, count * AES_BLOCK_SIZE);
	rep_xcrypt_ecb(tmp, out, key, cword, count);
}