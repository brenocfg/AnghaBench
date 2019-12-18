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
struct eap_peap_data {size_t phase2_key_len; int /*<<< orphan*/ * phase2_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void eap_peap_get_isk(struct eap_peap_data *data,
			     u8 *isk, size_t isk_len)
{
	size_t key_len;

	os_memset(isk, 0, isk_len);
	if (data->phase2_key == NULL)
		return;

	key_len = data->phase2_key_len;
	if (key_len > isk_len)
		key_len = isk_len;
	os_memcpy(isk, data->phase2_key, key_len);
}