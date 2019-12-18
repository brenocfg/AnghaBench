#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ base; scalar_t__ last; char** text; int /*<<< orphan*/  set; int /*<<< orphan*/  msgcat; } ;
typedef  TYPE_1__ resulttable ;
typedef  scalar_t__ isc_result_t ;

/* Variables and functions */
 TYPE_1__* ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 TYPE_1__* ISC_LIST_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_RESULT_UNAVAILABLESET ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initialize () ; 
 int /*<<< orphan*/  isc_msgcat ; 
 char* isc_msgcat_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  tables ; 

const char *
isc_result_totext(isc_result_t result) {
	resulttable *table;
	const char *txt, *default_text;
	int idx;

	initialize();

	LOCK(&lock);

	txt = NULL;
	for (table = ISC_LIST_HEAD(tables);
	     table != NULL;
	     table = ISC_LIST_NEXT(table, link)) {
		if (result >= table->base && result <= table->last) {
			idx = (int)(result - table->base);
			default_text = table->text[idx];
			/*
			 * Note: we use 'idx + 1' as the message number
			 * instead of idx because isc_msgcat_get() requires
			 * the message number to be > 0.
			 */
			txt = isc_msgcat_get(table->msgcat, table->set,
					     idx + 1, default_text);
			break;
		}
	}
	if (txt == NULL)
		txt = isc_msgcat_get(isc_msgcat, ISC_RESULT_UNAVAILABLESET,
				     1, "(result code text not available)");

	UNLOCK(&lock);

	return (txt);
}