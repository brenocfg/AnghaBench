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
typedef  int /*<<< orphan*/  _path ;

/* Variables and functions */
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static const char *
fixture_path(const char *base, const char *fixture_name)
{
	static char _path[4096];
	size_t root_len;

	root_len = strlen(base);
	strncpy(_path, base, sizeof(_path));

	if (_path[root_len - 1] != '/')
		_path[root_len++] = '/';

	if (fixture_name[0] == '/')
		fixture_name++;

	strncpy(_path + root_len,
		fixture_name,
		sizeof(_path) - root_len);

	return _path;
}