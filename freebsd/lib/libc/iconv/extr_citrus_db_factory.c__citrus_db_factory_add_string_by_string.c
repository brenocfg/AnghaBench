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
struct _region {int dummy; } ;
struct _citrus_db_factory {int dummy; } ;

/* Variables and functions */
 int _citrus_db_factory_add_by_string (struct _citrus_db_factory*,char const*,struct _region*,int) ; 
 int /*<<< orphan*/  _region_init (struct _region*,char*,scalar_t__) ; 
 int errno ; 
 char* strdup (char const*) ; 
 scalar_t__ strlen (char*) ; 

int
_citrus_db_factory_add_string_by_string(struct _citrus_db_factory *df,
    const char *key, const char *data)
{
	char *p;
	struct _region r;

	p = strdup(data);
	if (p == NULL)
		return (errno);
	_region_init(&r, p, strlen(p) + 1);
	return (_citrus_db_factory_add_by_string(df, key, &r, 1));
}