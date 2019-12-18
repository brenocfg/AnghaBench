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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int u_int ;
struct sockaddr_dl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int rsu_get_multi_pos (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
rsu_hash_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	uint32_t *mfilt = arg;
	uint8_t pos;

	pos = rsu_get_multi_pos(LLADDR(sdl));
	mfilt[pos / 32] |= (1 << (pos % 32));

	return (1);
}