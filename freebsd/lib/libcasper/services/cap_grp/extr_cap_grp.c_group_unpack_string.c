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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int ERANGE ; 
 char* nvlist_get_string (int /*<<< orphan*/  const*,char const*) ; 
 size_t strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static int
group_unpack_string(const nvlist_t *nvl, const char *fieldname, char **fieldp,
    char **bufferp, size_t *bufsizep)
{
	const char *str;
	size_t len;

	str = nvlist_get_string(nvl, fieldname);
	len = strlcpy(*bufferp, str, *bufsizep);
	if (len >= *bufsizep)
		return (ERANGE);
	*fieldp = *bufferp;
	*bufferp += len + 1;
	*bufsizep -= len + 1;

	return (0);
}