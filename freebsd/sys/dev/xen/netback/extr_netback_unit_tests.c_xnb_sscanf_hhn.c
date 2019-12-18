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
 scalar_t__ sscanf (char const*,char*,unsigned char*) ; 

__attribute__((used)) static void
xnb_sscanf_hhn(char *buffer, size_t buflen)
{
	const char mystr[] =
	    "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f"
	    "202122232425262728292a2b2c2d2e2f303132333435363738393a3b3c3d3e3f"
	    "404142434445464748494a4b4c4d4e4f505152535455565758595a5b5c5d5e5f";
	unsigned char dest[12];
	int i;

	for (i = 0; i < 12; i++)
		dest[i] = (unsigned char)'X';

	XNB_ASSERT(sscanf(mystr,
	    "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f"
	    "202122232425262728292a2b2c2d2e2f303132333435363738393a3b3c3d3e3f"
	    "404142434445464748494a4b4c4d4e4f%hhn", &dest[4]) == 0);
	for (i = 0; i < 12; i++)
		XNB_ASSERT(dest[i] == (i == 4 ? 160 : 'X'));
}