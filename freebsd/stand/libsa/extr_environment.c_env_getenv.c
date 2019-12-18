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
struct env_var {int /*<<< orphan*/  ev_name; struct env_var* ev_next; } ;

/* Variables and functions */
 struct env_var* environ ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

struct env_var	*
env_getenv(const char *name)
{
    struct env_var	*ev;
    
    for (ev = environ; ev != NULL; ev = ev->ev_next)
	if (!strcmp(ev->ev_name, name))
	    break;
    return(ev);
}