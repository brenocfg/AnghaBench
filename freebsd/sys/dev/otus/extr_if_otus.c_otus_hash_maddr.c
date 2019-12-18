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
 scalar_t__ LLADDR (struct sockaddr_dl*) ; 
 int le32dec (scalar_t__) ; 

__attribute__((used)) static u_int
otus_hash_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	uint32_t val, *hashes = arg;

	val = le32dec(LLADDR(sdl) + 4);
	/* Get address byte 5 */
	val = val & 0x0000ff00;
	val = val >> 8;

	/* As per below, shift it >> 2 to get only 6 bits */
	val = val >> 2;
	if (val < 32)
		hashes[0] |= 1 << val;
	else
		hashes[1] |= 1 << (val - 32);

	return (1);
}