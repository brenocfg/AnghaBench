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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_M_NOWAIT ; 
 char* ocs_malloc (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

char *
ocs_strdup(const char *s)
{
	uint32_t l = strlen(s);
	char *d;

	d = ocs_malloc(NULL, l+1, OCS_M_NOWAIT);
	if (d != NULL) {
		ocs_strcpy(d, s);
	}
	return d;
}