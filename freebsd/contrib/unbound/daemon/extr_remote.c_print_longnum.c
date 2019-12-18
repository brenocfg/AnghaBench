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
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int ssl_printf (int /*<<< orphan*/ *,char*,char const*,unsigned long,...) ; 

__attribute__((used)) static int
print_longnum(RES* ssl, const char* desc, size_t x)
{
	if(x > 1024*1024*1024) {
		/* more than a Gb */
		size_t front = x / (size_t)1000000;
		size_t back = x % (size_t)1000000;
		return ssl_printf(ssl, "%s%u%6.6u\n", desc, 
			(unsigned)front, (unsigned)back);
	} else {
		return ssl_printf(ssl, "%s%lu\n", desc, (unsigned long)x);
	}
}