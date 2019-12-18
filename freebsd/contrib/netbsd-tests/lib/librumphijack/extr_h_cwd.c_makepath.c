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
 char const* buf ; 
 char* prefix ; 
 int prefixlen ; 
 int /*<<< orphan*/  strcat (char const*,char const*) ; 
 int /*<<< orphan*/  strcpy (char const*,char*) ; 

__attribute__((used)) static const char *
makepath(const char *tail)
{

	strcpy(buf, prefix);
	if (prefix[prefixlen-1] != '/')
		strcat(buf, "/");
	strcat(buf, tail);

	return buf;
}