#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* authz; } ;
typedef  TYPE_2__ ctor_baton_t ;
struct TYPE_11__ {int /*<<< orphan*/  user; } ;
typedef  TYPE_3__ authz_global_rights_t ;
struct TYPE_9__ {int /*<<< orphan*/  user_rights; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 TYPE_3__* apr_palloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_global_rights (TYPE_3__*,char const*,int /*<<< orphan*/ ) ; 
 TYPE_3__* svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void
prepare_global_rights(ctor_baton_t *cb, const char *user)
{
  authz_global_rights_t *gr = svn_hash_gets(cb->authz->user_rights, user);
  if (!gr)
    {
      gr = apr_palloc(cb->authz->pool, sizeof(*gr));
      init_global_rights(gr, user, cb->authz->pool);
      svn_hash_sets(cb->authz->user_rights, gr->user, gr);
    }
}