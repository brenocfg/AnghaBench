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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  adm_dir_name ; 
 int /*<<< orphan*/  default_adm_dir_name ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

svn_boolean_t
svn_wc_is_adm_dir(const char *name, apr_pool_t *pool)
{
  return (0 == strcmp(name, adm_dir_name)
          || 0 == strcmp(name, default_adm_dir_name));
}