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
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  ecb_crypt_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cword*,int) ; 
 scalar_t__ ecb_fetch_bytes ; 
 scalar_t__ offset_in_page (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  rep_xcrypt_ecb (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cword*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void ecb_crypt(const u8 *in, u8 *out, u32 *key,
			     struct cword *cword, int count)
{
	/* Padlock in ECB mode fetches at least ecb_fetch_bytes of data.
	 * We could avoid some copying here but it's probably not worth it.
	 */
	if (unlikely(offset_in_page(in) + ecb_fetch_bytes > PAGE_SIZE)) {
		ecb_crypt_copy(in, out, key, cword, count);
		return;
	}

	rep_xcrypt_ecb(in, out, key, cword, count);
}