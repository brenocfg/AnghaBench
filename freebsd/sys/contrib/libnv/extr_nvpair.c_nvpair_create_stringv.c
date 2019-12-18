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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  nvpair_t ;

/* Variables and functions */
 int /*<<< orphan*/  nv_free (char*) ; 
 int nv_vasprintf (char**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvpair_create_string (char const*,char*) ; 

nvpair_t *
nvpair_create_stringv(const char *name, const char *valuefmt, va_list valueap)
{
	nvpair_t *nvp;
	char *str;
	int len;

	len = nv_vasprintf(&str, valuefmt, valueap);
	if (len < 0)
		return (NULL);
	nvp = nvpair_create_string(name, str);
	nv_free(str);
	return (nvp);
}