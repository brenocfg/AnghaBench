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
 int /*<<< orphan*/  efunc (int,char*) ; 
 char* strndup (char const*,size_t) ; 
 int /*<<< orphan*/  stub1 (int,char*) ; 

char *
estrndup(const char *s, size_t len)
{
	char *d = strndup(s, len);
	if (d == NULL)
		(*efunc)(1, "Cannot copy string");
	return d;
}