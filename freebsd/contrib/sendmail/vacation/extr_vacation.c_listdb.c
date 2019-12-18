#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_14__ {int (* smdb_cursor ) (TYPE_8__*,TYPE_2__**,int /*<<< orphan*/ ) ;} ;
struct TYPE_13__ {int (* smdbc_get ) (TYPE_2__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* smdbc_close ) (TYPE_2__*) ;} ;
struct TYPE_12__ {int size; scalar_t__ data; } ;
typedef  TYPE_1__ SMDB_DBENT ;
typedef  TYPE_2__ SMDB_CURSOR ;

/* Variables and functions */
 TYPE_8__* Db ; 
 int SMDBE_LAST_ENTRY ; 
 int SMDBE_OK ; 
 int /*<<< orphan*/  SMDB_CURSOR_GET_NEXT ; 
 int /*<<< orphan*/  SM_TIME_DEFAULT ; 
 int /*<<< orphan*/  VIT ; 
 char* ctime (scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,char,int) ; 
 int /*<<< orphan*/  sm_errstring (int) ; 
 int /*<<< orphan*/  sm_io_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  smioerr ; 
 int /*<<< orphan*/  smioout ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_8__*,TYPE_2__**,int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_2__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*) ; 

__attribute__((used)) static void
listdb()
{
	int result;
	time_t t;
	SMDB_CURSOR *cursor = NULL;
	SMDB_DBENT db_key, db_value;

	memset(&db_key, '\0', sizeof db_key);
	memset(&db_value, '\0', sizeof db_value);

	result = Db->smdb_cursor(Db, &cursor, 0);
	if (result != SMDBE_OK)
	{
		sm_io_fprintf(smioerr, SM_TIME_DEFAULT,
			      "vacation: set cursor: %s\n",
			      sm_errstring(result));
		return;
	}

	while ((result = cursor->smdbc_get(cursor, &db_key, &db_value,
					   SMDB_CURSOR_GET_NEXT)) == SMDBE_OK)
	{
		char *timestamp;

		/* skip magic VIT entry */
		if (db_key.size == strlen(VIT) + 1 &&
		    strncmp((char *)db_key.data, VIT,
			    (int)db_key.size - 1) == 0)
			continue;

		/* skip bogus values */
		if (db_value.size != sizeof t)
		{
			sm_io_fprintf(smioerr, SM_TIME_DEFAULT,
				      "vacation: %.*s invalid time stamp\n",
				      (int) db_key.size, (char *) db_key.data);
			continue;
		}

		memcpy(&t, db_value.data, sizeof t);

		if (db_key.size > 40)
			db_key.size = 40;

		if (t <= 0)
		{
			/* must be an exclude */
			timestamp = "(exclusion)\n";
		}
		else
		{
			timestamp = ctime(&t);
		}
		sm_io_fprintf(smioout, SM_TIME_DEFAULT, "%-40.*s %-10s",
			      (int) db_key.size, (char *) db_key.data,
			      timestamp);

		memset(&db_key, '\0', sizeof db_key);
		memset(&db_value, '\0', sizeof db_value);
	}

	if (result != SMDBE_OK && result != SMDBE_LAST_ENTRY)
	{
		sm_io_fprintf(smioerr, SM_TIME_DEFAULT,
			      "vacation: get value at cursor: %s\n",
			      sm_errstring(result));
		if (cursor != NULL)
		{
			(void) cursor->smdbc_close(cursor);
			cursor = NULL;
		}
		return;
	}
	(void) cursor->smdbc_close(cursor);
	cursor = NULL;
}