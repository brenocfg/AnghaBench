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
struct crypto_hash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_hash_update (struct crypto_hash*,int /*<<< orphan*/  const*,size_t) ; 

void eap_pwd_h_update(struct crypto_hash *hash, const u8 *data, size_t len)
{
	crypto_hash_update(hash, data, len);
}