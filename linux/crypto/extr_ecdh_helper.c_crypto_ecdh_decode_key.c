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
typedef  char u8 ;
struct kpp_secret {scalar_t__ type; scalar_t__ len; } ;
struct ecdh {void* key; struct kpp_secret key_size; struct kpp_secret curve_id; } ;
typedef  int /*<<< orphan*/  secret ;

/* Variables and functions */
 scalar_t__ CRYPTO_KPP_SECRET_TYPE_ECDH ; 
 unsigned int ECDH_KPP_SECRET_MIN_SIZE ; 
 int EINVAL ; 
 scalar_t__ crypto_ecdh_key_len (struct ecdh*) ; 
 char* ecdh_unpack_data (struct kpp_secret*,char const*,int) ; 
 scalar_t__ unlikely (int) ; 

int crypto_ecdh_decode_key(const char *buf, unsigned int len,
			   struct ecdh *params)
{
	const u8 *ptr = buf;
	struct kpp_secret secret;

	if (unlikely(!buf || len < ECDH_KPP_SECRET_MIN_SIZE))
		return -EINVAL;

	ptr = ecdh_unpack_data(&secret, ptr, sizeof(secret));
	if (secret.type != CRYPTO_KPP_SECRET_TYPE_ECDH)
		return -EINVAL;

	ptr = ecdh_unpack_data(&params->curve_id, ptr, sizeof(params->curve_id));
	ptr = ecdh_unpack_data(&params->key_size, ptr, sizeof(params->key_size));
	if (secret.len != crypto_ecdh_key_len(params))
		return -EINVAL;

	/* Don't allocate memory. Set pointer to data
	 * within the given buffer
	 */
	params->key = (void *)ptr;

	return 0;
}