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
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char const*,...) ; 

__attribute__((used)) static void
print_ext_speed(u_char x, int scale)
{
	static const char *mant[] =
	{"Reserved", "1.0", "1.2", "1.3", "1.5", "2.0", "2.5", "3.0",
	"3.5", "4.0", "4.5", "5.0", "5.5", "6.0", "7.0", "8.0"};
	static const char *exp[] =
	{"1 ns", "10 ns", "100 ns", "1 us", "10 us", "100 us",
	"1 ms", "10 ms"};
	static const char *scale_name[] =
	{"None", "10", "100", "1,000", "10,000", "100,000",
	"1,000,000", "10,000,000"};

	printf("Speed = %s x %s", mant[(x >> 3) & 0xF], exp[x & 7]);
	if (scale)
		printf(", scaled by %s", scale_name[scale & 7]);
}