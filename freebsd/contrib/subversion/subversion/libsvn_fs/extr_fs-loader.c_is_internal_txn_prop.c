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
typedef  int svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_FS__PROP_TXN_CHECK_LOCKS ; 
 int /*<<< orphan*/  SVN_FS__PROP_TXN_CHECK_OOD ; 
 int /*<<< orphan*/  SVN_FS__PROP_TXN_CLIENT_DATE ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_boolean_t
is_internal_txn_prop(const char *name)
{
  return strcmp(name, SVN_FS__PROP_TXN_CHECK_LOCKS) == 0 ||
         strcmp(name, SVN_FS__PROP_TXN_CHECK_OOD) == 0 ||
         strcmp(name, SVN_FS__PROP_TXN_CLIENT_DATE) == 0;
}