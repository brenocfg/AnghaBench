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

/* Variables and functions */
 char* _pico_alloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

char *_pico_clone_alloc( const char *str ) {
	char* cloned;

	/* sanity check */
	if ( str == NULL ) {
		return NULL;
	}

	/* allocate memory */
	cloned = _pico_alloc(strlen(str) + 1);
	if ( cloned == NULL ) {
		return NULL;
	}

	/* copy input string to cloned string */
	strcpy(cloned, str);

	/* return ptr to cloned string */
	return cloned;
}