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
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/ * krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HEIMDAL_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEIMDAL_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HEIMDAL_setspecific (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  context_key ; 
 int /*<<< orphan*/  context_mutex ; 
 int created_key ; 
 int /*<<< orphan*/  destroy_context ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ **) ; 

krb5_error_code
_gsskrb5_init (krb5_context *context)
{
    krb5_error_code ret = 0;

    HEIMDAL_MUTEX_lock(&context_mutex);

    if (!created_key) {
	HEIMDAL_key_create(&context_key, destroy_context, ret);
	if (ret) {
	    HEIMDAL_MUTEX_unlock(&context_mutex);
	    return ret;
	}
	created_key = 1;
    }
    HEIMDAL_MUTEX_unlock(&context_mutex);

    *context = HEIMDAL_getspecific(context_key);
    if (*context == NULL) {

	ret = krb5_init_context(context);
	if (ret == 0) {
	    HEIMDAL_setspecific(context_key, *context, ret);
	    if (ret) {
		krb5_free_context(*context);
		*context = NULL;
	    }
	}
    }

    return ret;
}