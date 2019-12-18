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
typedef  int /*<<< orphan*/  ubuf ;
typedef  int /*<<< orphan*/  const u8 ;
struct shash_desc {struct crypto_shash* tfm; } ;
struct shash_alg {int (* update ) (struct shash_desc*,int /*<<< orphan*/  const*,unsigned int) ;} ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_ALGAPI_ALIGNMASK ; 
 int /*<<< orphan*/  const* PTR_ALIGN (int /*<<< orphan*/  const*,unsigned long) ; 
 scalar_t__ WARN_ON (int) ; 
 struct shash_alg* crypto_shash_alg (struct crypto_shash*) ; 
 unsigned long crypto_shash_alignmask (struct crypto_shash*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned int) ; 
 int stub1 (struct shash_desc*,int /*<<< orphan*/  const*,unsigned int) ; 
 int stub2 (struct shash_desc*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int shash_update_unaligned(struct shash_desc *desc, const u8 *data,
				  unsigned int len)
{
	struct crypto_shash *tfm = desc->tfm;
	struct shash_alg *shash = crypto_shash_alg(tfm);
	unsigned long alignmask = crypto_shash_alignmask(tfm);
	unsigned int unaligned_len = alignmask + 1 -
				     ((unsigned long)data & alignmask);
	/*
	 * We cannot count on __aligned() working for large values:
	 * https://patchwork.kernel.org/patch/9507697/
	 */
	u8 ubuf[MAX_ALGAPI_ALIGNMASK * 2];
	u8 *buf = PTR_ALIGN(&ubuf[0], alignmask + 1);
	int err;

	if (WARN_ON(buf + unaligned_len > ubuf + sizeof(ubuf)))
		return -EINVAL;

	if (unaligned_len > len)
		unaligned_len = len;

	memcpy(buf, data, unaligned_len);
	err = shash->update(desc, buf, unaligned_len);
	memset(buf, 0, unaligned_len);

	return err ?:
	       shash->update(desc, data + unaligned_len, len - unaligned_len);
}