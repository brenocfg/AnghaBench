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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_FS_PROP_BASEVALUE_MISMATCH ; 
 int /*<<< orphan*/ * svn_error_find_cause (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_boolean_t is_atomicity_error(svn_error_t *err)
{
  return svn_error_find_cause(err, SVN_ERR_FS_PROP_BASEVALUE_MISMATCH) != NULL;
}