#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct passwd {TYPE_1__** pw_name; } ;
struct TYPE_19__ {int (* get ) (TYPE_4__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* put ) (TYPE_4__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_18__ {int size; TYPE_1__** data; } ;
struct TYPE_17__ {int /*<<< orphan*/ * whead; } ;
typedef  TYPE_1__ PERSON ;
typedef  TYPE_2__ DBT ;

/* Variables and functions */
 int /*<<< orphan*/  DB_BTREE ; 
 int /*<<< orphan*/  O_RDWR ; 
 TYPE_4__* db ; 
 TYPE_4__* dbopen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  memmove (TYPE_1__**,TYPE_1__**,int) ; 
 TYPE_1__* palloc () ; 
 int strlen (TYPE_1__**) ; 
 int stub1 (TYPE_4__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  userinfo (TYPE_1__*,struct passwd*) ; 

PERSON *
enter_person(struct passwd *pw)
{
	DBT data, key;
	PERSON *pn;

	if (db == NULL &&
	    (db = dbopen(NULL, O_RDWR, 0, DB_BTREE, NULL)) == NULL)
		err(1, NULL);

	key.data = pw->pw_name;
	key.size = strlen(pw->pw_name);

	switch ((*db->get)(db, &key, &data, 0)) {
	case 0:
		memmove(&pn, data.data, sizeof pn);
		return (pn);
	default:
	case -1:
		err(1, "db get");
		/* NOTREACHED */
	case 1:
		++entries;
		pn = palloc();
		userinfo(pn, pw);
		pn->whead = NULL;

		data.size = sizeof(PERSON *);
		data.data = &pn;
		if ((*db->put)(db, &key, &data, 0))
			err(1, "db put");
		return (pn);
	}
}