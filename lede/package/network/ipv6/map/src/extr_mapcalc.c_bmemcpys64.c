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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 size_t be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bmemcpy (void*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  cpu_to_be64 (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void bmemcpys64(void *av, const void *bv, size_t frombits, size_t nbits)
{
	uint64_t buf = 0;
	const uint8_t *b = bv;
	size_t frombyte = frombits / 8, tobyte = (frombits + nbits) / 8;

	memcpy(&buf, &b[frombyte], tobyte - frombyte + 1);
	buf = cpu_to_be64(be64_to_cpu(buf) << (frombits % 8));

	bmemcpy(av, &buf, nbits);
}