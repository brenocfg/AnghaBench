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
typedef  int uint32_t ;
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_MACCMD ; 
 int BWN_MACCMD_BGNOISE ; 
 int BWN_READ_4 (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_SHARED ; 
 int /*<<< orphan*/  BWN_WRITE_4 (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bwn_shm_write_2 (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
bwn_noise_gensample(struct bwn_mac *mac)
{
	uint32_t jssi = 0x7f7f7f7f;

	bwn_shm_write_2(mac, BWN_SHARED, 0x088, (jssi & 0x0000ffff));
	bwn_shm_write_2(mac, BWN_SHARED, 0x08a, (jssi & 0xffff0000) >> 16);
	BWN_WRITE_4(mac, BWN_MACCMD,
	    BWN_READ_4(mac, BWN_MACCMD) | BWN_MACCMD_BGNOISE);
}