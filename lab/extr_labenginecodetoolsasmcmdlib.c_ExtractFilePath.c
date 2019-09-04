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
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

void ExtractFilePath (const char *path, char *dest)
{
	const char    *src;

	src = path + strlen(path) - 1;

//
// back up until a \ or the start
//
	while (src != path && *(src-1) != '\\' && *(src-1) != '/')
		src--;

	memcpy (dest, path, src-path);
	dest[src-path] = 0;
}