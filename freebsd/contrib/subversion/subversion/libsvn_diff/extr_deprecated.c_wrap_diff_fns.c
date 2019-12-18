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
typedef  int /*<<< orphan*/  svn_diff_fns_t ;
struct TYPE_3__ {int /*<<< orphan*/  token_discard_all; int /*<<< orphan*/  token_discard; int /*<<< orphan*/  token_compare; int /*<<< orphan*/  datasource_get_next_token; int /*<<< orphan*/  datasource_close; int /*<<< orphan*/  datasources_open; } ;
typedef  TYPE_1__ svn_diff_fns2_t ;
struct fns_wrapper_baton {int /*<<< orphan*/  const* vtable; void* old_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  datasource_close ; 
 int /*<<< orphan*/  datasource_get_next_token ; 
 int /*<<< orphan*/  datasources_open ; 
 int /*<<< orphan*/  token_compare ; 
 int /*<<< orphan*/  token_discard ; 
 int /*<<< orphan*/  token_discard_all ; 

__attribute__((used)) static void
wrap_diff_fns(svn_diff_fns2_t **diff_fns2,
              struct fns_wrapper_baton **baton2,
              const svn_diff_fns_t *diff_fns,
              void *baton,
              apr_pool_t *result_pool)
{
  /* Initialize the return vtable. */
  *diff_fns2 = apr_palloc(result_pool, sizeof(**diff_fns2));

  (*diff_fns2)->datasources_open = datasources_open;
  (*diff_fns2)->datasource_close = datasource_close;
  (*diff_fns2)->datasource_get_next_token = datasource_get_next_token;
  (*diff_fns2)->token_compare = token_compare;
  (*diff_fns2)->token_discard = token_discard;
  (*diff_fns2)->token_discard_all = token_discard_all;

  /* Initialize the wrapper baton. */
  *baton2 = apr_palloc(result_pool, sizeof (**baton2));
  (*baton2)->old_baton = baton;
  (*baton2)->vtable = diff_fns;
}