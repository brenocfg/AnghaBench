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
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heim_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * modules ; 
 int /*<<< orphan*/  plugin_mutex ; 

void
_krb5_unload_plugins(krb5_context context, const char *name)
{
    HEIMDAL_MUTEX_lock(&plugin_mutex);
    heim_release(modules);
    modules = NULL;
    HEIMDAL_MUTEX_unlock(&plugin_mutex);
}