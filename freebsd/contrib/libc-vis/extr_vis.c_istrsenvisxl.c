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
 int istrsenvisx (char**,size_t*,char const*,int /*<<< orphan*/ ,int,char const*,int*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int
istrsenvisxl(char **mbdstp, size_t *dlen, const char *mbsrc,
    int flags, const char *mbextra, int *cerr_ptr)
{
	return istrsenvisx(mbdstp, dlen, mbsrc,
	    mbsrc != NULL ? strlen(mbsrc) : 0, flags, mbextra, cerr_ptr);
}