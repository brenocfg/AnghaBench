#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int svn_boolean_t ;
struct TYPE_5__ {scalar_t__ env; TYPE_1__* bdb; } ;
typedef  TYPE_2__ bdb_env_baton_t ;
struct TYPE_4__ {scalar_t__ env; int /*<<< orphan*/  panic; } ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  svn_atomic_read (int /*<<< orphan*/ *) ; 

svn_boolean_t
svn_fs_bdb__get_panic(bdb_env_baton_t *bdb_baton)
{
  /* An invalid baton is equivalent to a panicked environment; in both
     cases, database cleanups should be skipped. */
  if (!bdb_baton->bdb)
    return TRUE;

  assert(bdb_baton->env == bdb_baton->bdb->env);
  return !!svn_atomic_read(&bdb_baton->bdb->panic);
}