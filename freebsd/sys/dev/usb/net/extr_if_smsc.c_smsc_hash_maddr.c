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
typedef  int u_int ;
struct sockaddr_dl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int smsc_hash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
smsc_hash_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	uint32_t hash, *hashtbl = arg;

	hash = smsc_hash(LLADDR(sdl));
	hashtbl[hash >> 5] |= 1 << (hash & 0x1F);

	return (1);
}