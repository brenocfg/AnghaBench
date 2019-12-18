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
typedef  scalar_t__ uid_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asprintf (char**,char*,long,unsigned int) ; 
 int /*<<< orphan*/  ccache_mutex ; 
 unsigned int ccache_nextid ; 

char *kcm_ccache_nextid(pid_t pid, uid_t uid, gid_t gid)
{
    unsigned n;
    char *name;

    HEIMDAL_MUTEX_lock(&ccache_mutex);
    n = ++ccache_nextid;
    HEIMDAL_MUTEX_unlock(&ccache_mutex);

    asprintf(&name, "%ld:%u", (long)uid, n);

    return name;
}