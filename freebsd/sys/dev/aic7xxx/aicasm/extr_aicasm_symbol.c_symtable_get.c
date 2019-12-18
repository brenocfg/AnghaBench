#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbol_t ;
typedef  int /*<<< orphan*/  stored_ptr ;
typedef  int /*<<< orphan*/  new_symbol ;
struct TYPE_10__ {int (* get ) (TYPE_2__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ;scalar_t__ (* put ) (TYPE_2__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int size; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_1__ DBT ;

/* Variables and functions */
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/ ** strdup (char const*) ; 
 int strlen (char const*) ; 
 int stub1 (TYPE_2__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_2__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * symbol_create (char const*) ; 
 TYPE_2__* symtable ; 

symbol_t *
symtable_get(const char *name)
{
	symbol_t *stored_ptr;
	DBT	  key;
	DBT	  data;
	int	  retval;

	key.data = strdup(name);
	key.size = strlen(name);

	if ((retval = symtable->get(symtable, &key, &data, /*flags*/0)) != 0) {
		if (retval == -1) {
			perror("Symbol table get operation failed");
			exit(EX_SOFTWARE);
			/* NOTREACHED */
		} else if (retval == 1) {
			/* Symbol wasn't found, so create a new one */
			symbol_t *new_symbol;

			new_symbol = symbol_create(name);
			data.data = &new_symbol;
			data.size = sizeof(new_symbol);
			if (symtable->put(symtable, &key, &data,
					  /*flags*/0) !=0) {
				perror("Symtable put failed");
				exit(EX_SOFTWARE);
			}
			free(key.data);
			return (new_symbol);
		} else {
			perror("Unexpected return value from db get routine");
			exit(EX_SOFTWARE);
			/* NOTREACHED */
		}
	}
	memcpy(&stored_ptr, data.data, sizeof(stored_ptr));
	free(key.data);
	return (stored_ptr);
}