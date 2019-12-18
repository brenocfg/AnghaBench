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
 int strcmp (char* const,char* const) ; 
 int strcoll (char* const,char* const) ; 

__attribute__((used)) static int
compare(const void *p, const void *q)
{
#if defined(NLS) && defined(HAVE_STRCOLL)
    return (strcoll(*(char *const *) p, *(char *const *) q));
#else
    return (strcmp(*(char *const *) p, *(char *const *) q));
#endif /* NLS && HAVE_STRCOLL */
}