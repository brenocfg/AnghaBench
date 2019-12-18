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

/* Variables and functions */
 int /*<<< orphan*/  XNB_ASSERT (int) ; 
 int sscanf (char const*,char*,int*) ; 

__attribute__((used)) static void
xnb_sscanf_hhu(char *buffer, size_t buflen)
{
	const char mystr[] = "137";
	uint8_t dest[12];
	int i;

	for (i = 0; i < 12; i++)
		dest[i] = 'X';

	XNB_ASSERT(sscanf(mystr, "%hhu", &dest[4]) == 1);
	for (i = 0; i < 12; i++)
		XNB_ASSERT(dest[i] == (i == 4 ? 137 : 'X'));
}