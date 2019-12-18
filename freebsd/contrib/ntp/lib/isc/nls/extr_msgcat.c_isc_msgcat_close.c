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
typedef  scalar_t__ nl_catd ;
struct TYPE_5__ {scalar_t__ catalog; scalar_t__ magic; } ;
typedef  TYPE_1__ isc_msgcat_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int) ; 
 scalar_t__ VALID_MSGCAT (TYPE_1__*) ; 
 int /*<<< orphan*/  catclose (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
isc_msgcat_close(isc_msgcat_t **msgcatp) {
	isc_msgcat_t *msgcat;

	/*
	 * Close a message catalog.
	 */

	REQUIRE(msgcatp != NULL);
	msgcat = *msgcatp;
	REQUIRE(VALID_MSGCAT(msgcat) || msgcat == NULL);

	if (msgcat != NULL) {
#ifdef HAVE_CATGETS
		if (msgcat->catalog != (nl_catd)(-1))
			(void)catclose(msgcat->catalog);
#endif
		msgcat->magic = 0;
		free(msgcat);
	}

	*msgcatp = NULL;
}