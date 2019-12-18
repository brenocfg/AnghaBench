#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  magic; int /*<<< orphan*/  catalog; } ;
typedef  TYPE_1__ isc_msgcat_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSGCAT_MAGIC ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  catopen (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int) ; 

void
isc_msgcat_open(const char *name, isc_msgcat_t **msgcatp) {
	isc_msgcat_t *msgcat;

	/*
	 * Open a message catalog.
	 */

	REQUIRE(name != NULL);
	REQUIRE(msgcatp != NULL && *msgcatp == NULL);

	msgcat = malloc(sizeof(*msgcat));
	if (msgcat == NULL) {
		*msgcatp = NULL;
		return;
	}

#ifdef HAVE_CATGETS
	/*
	 * We don't check if catopen() fails because we don't care.
	 * If it does fail, then when we call catgets(), it will use
	 * the default string.
	 */
	msgcat->catalog = catopen(name, 0);
#endif
	msgcat->magic = MSGCAT_MAGIC;

	*msgcatp = msgcat;
}