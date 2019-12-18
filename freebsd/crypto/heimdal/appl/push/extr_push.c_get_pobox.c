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
 int /*<<< orphan*/  errx (int,char*) ; 
 char* getenv (char*) ; 
 char* hesiod_get_pobox (char const**) ; 

__attribute__((used)) static char *
get_pobox (const char **user)
{
    char *ret = NULL;

#ifdef HESIOD
    ret = hesiod_get_pobox (user);
#endif

    if (ret == NULL)
	ret = getenv("MAILHOST");
    if (ret == NULL)
	errx (1, "MAILHOST not set");
    return ret;
}