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
typedef  int /*<<< orphan*/  DBTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  DB_BTREE ; 
 int /*<<< orphan*/  DB_HASH ; 
 int /*<<< orphan*/  DB_RECNO ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static DBTYPE
dbtype(const char *s)
{
	if (!strcmp(s, "btree"))
		return DB_BTREE;
	if (!strcmp(s, "hash"))
		return DB_HASH;
	if (!strcmp(s, "recno"))
		return DB_RECNO;
	errx(1, "%s: unknown type (use btree, hash or recno)", s);
	/* NOTREACHED */
}