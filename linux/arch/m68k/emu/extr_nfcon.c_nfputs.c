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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  nf_call (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stderr_id ; 
 unsigned long virt_to_phys (char*) ; 

__attribute__((used)) static void nfputs(const char *str, unsigned int count)
{
	char buf[68];
	unsigned long phys = virt_to_phys(buf);

	buf[64] = 0;
	while (count > 64) {
		memcpy(buf, str, 64);
		nf_call(stderr_id, phys);
		str += 64;
		count -= 64;
	}
	memcpy(buf, str, count);
	buf[count] = 0;
	nf_call(stderr_id, phys);
}