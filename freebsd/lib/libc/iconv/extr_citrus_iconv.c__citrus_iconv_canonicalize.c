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
 scalar_t__ PATH_MAX ; 
 int /*<<< orphan*/  _citrus_esdb_alias (char const*,char*,size_t) ; 
 char* calloc (size_t,int) ; 

const char
*_citrus_iconv_canonicalize(const char *name)
{
	char *buf;

	if ((buf = calloc((size_t)PATH_MAX, sizeof(*buf))) == NULL)
		return (NULL);
	_citrus_esdb_alias(name, buf, (size_t)PATH_MAX);
	return (buf);
}