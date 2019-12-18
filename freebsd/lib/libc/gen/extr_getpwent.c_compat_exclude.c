#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int (* put ) (TYPE_2__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {char* data; scalar_t__ size; } ;
typedef  TYPE_1__ DBT ;
typedef  TYPE_2__ DB ;

/* Variables and functions */
 int /*<<< orphan*/  DB_HASH ; 
 int /*<<< orphan*/  O_RDWR ; 
 TYPE_2__* dbopen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 
 scalar_t__ strlen (char const*) ; 
 int stub1 (TYPE_2__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compat_exclude(const char *name, DB **db)
{
	DBT	key, data;

	if (*db == NULL &&
	    (*db = dbopen(NULL, O_RDWR, 600, DB_HASH, 0)) == NULL)
		return (errno);
	key.size = strlen(name);
	key.data = (char *)name;
	data.size = 0;
	data.data = NULL;

	if ((*db)->put(*db, &key, &data, 0) == -1)
		return (errno);
	return (0);
}