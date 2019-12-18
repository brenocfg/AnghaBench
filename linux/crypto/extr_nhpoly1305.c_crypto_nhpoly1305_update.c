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
 int crypto_nhpoly1305_update_helper (struct shash_desc*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nh_generic ; 

int crypto_nhpoly1305_update(struct shash_desc *desc,
			     const u8 *src, unsigned int srclen)
{
	return crypto_nhpoly1305_update_helper(desc, src, srclen, nh_generic);
}