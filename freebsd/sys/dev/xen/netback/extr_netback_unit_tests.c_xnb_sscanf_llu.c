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
 int /*<<< orphan*/  XNB_ASSERT (int) ; 
 int sscanf (char const*,char*,unsigned long long*) ; 

__attribute__((used)) static void
xnb_sscanf_llu(char *buffer, size_t buflen)
{
	const char mystr[] = "12802747070103273189";
	unsigned long long dest[3];
	int i;

	for (i = 0; i < 3; i++)
		dest[i] = (long long)0xdeadbeefdeadbeef;

	XNB_ASSERT(sscanf(mystr, "%llu", &dest[1]) == 1);
	for (i = 0; i < 3; i++)
		XNB_ASSERT(dest[i] == (i != 1 ? (long long)0xdeadbeefdeadbeef :
		    12802747070103273189ull));
}