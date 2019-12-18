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
 int istrsenvisxl (char**,size_t*,char const*,int,char const*,int /*<<< orphan*/ *) ; 

int
strsnvis(char *mbdst, size_t dlen, const char *mbsrc, int flags, const char *mbextra)
{
	return istrsenvisxl(&mbdst, &dlen, mbsrc, flags, mbextra, NULL);
}