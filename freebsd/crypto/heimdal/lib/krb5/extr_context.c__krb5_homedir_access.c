#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* krb5_context ;
typedef  int /*<<< orphan*/  krb5_boolean ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int KRB5_CTX_F_HOMEDIR_ACCESS ; 
 int /*<<< orphan*/  allow_homedir ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  homedir_mutex ; 

krb5_boolean
_krb5_homedir_access(krb5_context context)
{
    krb5_boolean allow;

#ifdef HAVE_GETEUID
    /* is never allowed for root */
    if (geteuid() == 0)
	return FALSE;
#endif

    if (context && (context->flags & KRB5_CTX_F_HOMEDIR_ACCESS) == 0)
	return FALSE;

    HEIMDAL_MUTEX_lock(&homedir_mutex);
    allow = allow_homedir;
    HEIMDAL_MUTEX_unlock(&homedir_mutex);
    return allow;
}