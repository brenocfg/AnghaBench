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
struct env_var {char* ev_value; } ;

/* Variables and functions */
 struct env_var* env_getenv (char const*) ; 

char *
getenv(const char *name)
{
    struct env_var	*ev;

    /* Set but no value gives empty string */
    if ((ev = env_getenv(name)) != NULL) {
	if (ev->ev_value != NULL)
	    return(ev->ev_value);
	return("");
    }
    return(NULL);
}