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
struct _citrus_region {int dummy; } ;
struct _citrus_db_factory {int dummy; } ;

/* Variables and functions */
 int _citrus_db_factory_add (struct _citrus_db_factory*,struct _region*,int,struct _citrus_region*,int) ; 
 int /*<<< orphan*/  _region_init (struct _region*,char*,int /*<<< orphan*/ ) ; 
 int errno ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int
_citrus_db_factory_add_by_string(struct _citrus_db_factory *df,
    const char *key, struct _citrus_region *data, int datafree)
{
	struct _region r;
	char *tmp;

	tmp = strdup(key);
	if (tmp == NULL)
		return (errno);
	_region_init(&r, tmp, strlen(key));
	return _citrus_db_factory_add(df, &r, 1, data, datafree);
}