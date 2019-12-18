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
struct ttyent {char const* ty_type; } ;

/* Variables and functions */
 struct ttyent* getttynam (char*) ; 

const char *
stypeof(char *ttyid)
{
	struct ttyent *t;

	if (ttyid != NULL && *ttyid != '\0') {
		t = getttynam(ttyid);
		if (t != NULL && t->ty_type != NULL)
			return (t->ty_type);
	}
	return (NULL);
}