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
struct env_var {int (* ev_unsethook ) (struct env_var*) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  env_discard (struct env_var*) ; 
 struct env_var* env_getenv (char const*) ; 
 int stub1 (struct env_var*) ; 

int
unsetenv(const char *name)
{
    struct env_var	*ev;
    int			err;

    err = 0;
    if ((ev = env_getenv(name)) == NULL) {
	err = ENOENT;
    } else {
	if (ev->ev_unsethook != NULL)
	    err = ev->ev_unsethook(ev);
	if (err == 0) {
	    env_discard(ev);
	}
    }
    return(err);
}