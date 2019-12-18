#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  refcount; int /*<<< orphan*/  error_info; int /*<<< orphan*/ * dbconfig_file; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_1__ bdb_env_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  apr_threadkey_private_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 

__attribute__((used)) static apr_status_t
cleanup_env(void *data)
{
  bdb_env_t *bdb = data;
  bdb->pool = NULL;
  bdb->dbconfig_file = NULL;   /* will be closed during pool destruction */
#if APR_HAS_THREADS
  apr_threadkey_private_delete(bdb->error_info);
#endif /* APR_HAS_THREADS */

  /* If there are no references to this descriptor, free its memory here,
     so that we don't leak it if create_env returns an error.
     See bdb_close, which takes care of freeing this memory if the
     environment is still open when the cache is destroyed. */
  if (!bdb->refcount)
    free(data);

  return APR_SUCCESS;
}