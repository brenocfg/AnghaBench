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

__attribute__((used)) static char
nfsrv_hexdigit(char c, int *err)
{

	*err = 0;
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + ((char)10));
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + ((char)10));
	/* Not valid ! */
	*err = 1;
	return (1);	/* BOGUS */
}