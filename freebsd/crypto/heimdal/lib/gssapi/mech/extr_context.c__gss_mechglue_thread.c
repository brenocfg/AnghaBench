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
struct mg_thread_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 struct mg_thread_ctx* HEIMDAL_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEIMDAL_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HEIMDAL_setspecific (int /*<<< orphan*/ ,struct mg_thread_ctx*,int) ; 
 struct mg_thread_ctx* calloc (int,int) ; 
 int /*<<< orphan*/  context_key ; 
 int /*<<< orphan*/  context_mutex ; 
 int created_key ; 
 int /*<<< orphan*/  destroy_context ; 
 int /*<<< orphan*/  free (struct mg_thread_ctx*) ; 

__attribute__((used)) static struct mg_thread_ctx *
_gss_mechglue_thread(void)
{
    struct mg_thread_ctx *ctx;
    int ret = 0;

    HEIMDAL_MUTEX_lock(&context_mutex);

    if (!created_key) {
	HEIMDAL_key_create(&context_key, destroy_context, ret);
	if (ret) {
	    HEIMDAL_MUTEX_unlock(&context_mutex);
	    return NULL;
	}
	created_key = 1;
    }
    HEIMDAL_MUTEX_unlock(&context_mutex);

    ctx = HEIMDAL_getspecific(context_key);
    if (ctx == NULL) {

	ctx = calloc(1, sizeof(*ctx));
	if (ctx == NULL)
	    return NULL;
	HEIMDAL_setspecific(context_key, ctx, ret);
	if (ret) {
	    free(ctx);
	    return NULL;
	}
    }
    return ctx;
}