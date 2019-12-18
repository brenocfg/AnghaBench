#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  long long uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
typedef  int u_int ;
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_3__ {int time_mid; int time_hi_and_version; int clock_seq_hi_and_reserved; int clock_seq_low; int* node; scalar_t__ time_low; } ;
typedef  TYPE_1__ mkimg_uuid_t ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int random () ; 

__attribute__((used)) static void
osdep_uuidgen(mkimg_uuid_t *uuid)
{
	struct timeval tv;
	uint64_t time = 0x01B21DD213814000LL;
	u_int i;
	uint16_t seq;

	if (gettimeofday(&tv, NULL) == -1)
		abort();

	time += (uint64_t)tv.tv_sec * 10000000LL;
	time += tv.tv_usec * 10;

	uuid->time_low = (uint32_t)time;
	uuid->time_mid = (uint16_t)(time >> 32);
	uuid->time_hi_and_version = (uint16_t)(time >> 48) & 0xfff;
	uuid->time_hi_and_version |= 1 << 12;

	seq = random();

	uuid->clock_seq_hi_and_reserved = (uint8_t)(seq >> 8) & 0x3f;
	uuid->clock_seq_low = (uint8_t)seq;

	for (i = 0; i < 6; i++)
		uuid->node[i] = (uint8_t)random();
	uuid->node[0] |= 0x01;
}