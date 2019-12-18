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
struct shash_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crc32c_vpmsum (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/ * shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int crc32c_vpmsum_update(struct shash_desc *desc, const u8 *data,
			       unsigned int len)
{
	u32 *crcp = shash_desc_ctx(desc);

	*crcp = crc32c_vpmsum(*crcp, data, len);

	return 0;
}