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
struct TYPE_4__ {int /*<<< orphan*/  catalog; } ;
typedef  TYPE_1__ isc_msgcat_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int) ; 
 scalar_t__ VALID_MSGCAT (TYPE_1__*) ; 
 char const* catgets (int /*<<< orphan*/ ,int,int,char const*) ; 

const char *
isc_msgcat_get(isc_msgcat_t *msgcat, int set, int message,
	       const char *default_text)
{
	/*
	 * Get message 'message' from message set 'set' in 'msgcat'.  If it
	 * is not available, use 'default'.
	 */

	REQUIRE(VALID_MSGCAT(msgcat) || msgcat == NULL);
	REQUIRE(set > 0);
	REQUIRE(message > 0);
	REQUIRE(default_text != NULL);

#ifdef HAVE_CATGETS
	if (msgcat == NULL)
		return (default_text);
	return (catgets(msgcat->catalog, set, message, default_text));
#else
	return (default_text);
#endif
}