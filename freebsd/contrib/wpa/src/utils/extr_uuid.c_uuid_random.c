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
typedef  int u8 ;
typedef  int /*<<< orphan*/  t ;
struct os_time {int dummy; } ;

/* Variables and functions */
 int SHA256_MAC_LEN ; 
 int /*<<< orphan*/  UUID_LEN ; 
 scalar_t__ hmac_sha256 (int*,int /*<<< orphan*/ ,int const*,int,int*) ; 
 scalar_t__ os_get_random (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_get_time (struct os_time*) ; 
 int /*<<< orphan*/  os_memcpy (int*,int*,int /*<<< orphan*/ ) ; 

int uuid_random(u8 *uuid)
{
	struct os_time t;
	u8 hash[SHA256_MAC_LEN];

	/* Use HMAC-SHA256 and timestamp as context to avoid exposing direct
	 * os_get_random() output in the UUID field. */
	os_get_time(&t);
	if (os_get_random(uuid, UUID_LEN) < 0 ||
	    hmac_sha256(uuid, UUID_LEN, (const u8 *) &t, sizeof(t), hash) < 0)
		return -1;

	os_memcpy(uuid, hash, UUID_LEN);

	/* Version: 4 = random */
	uuid[6] = (4 << 4) | (uuid[6] & 0x0f);

	/* Variant specified in RFC 4122 */
	uuid[8] = 0x80 | (uuid[8] & 0x3f);

	return 0;
}