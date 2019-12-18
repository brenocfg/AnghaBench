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
 int istrsenvisx (char**,size_t*,char const*,size_t,int,char const*,int /*<<< orphan*/ *) ; 

int
strsnvisx(char *mbdst, size_t dlen, const char *mbsrc, size_t len, int flags,
    const char *mbextra)
{
	return istrsenvisx(&mbdst, &dlen, mbsrc, len, flags, mbextra, NULL);
}