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
typedef  int /*<<< orphan*/  svn_wc_relocation_validator2_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct compat2_baton {void* baton; int /*<<< orphan*/  validator; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  compat2_validator ; 
 int /*<<< orphan*/ * svn_wc_relocate3 (char const*,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compat2_baton*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_relocate2(const char *path,
                 svn_wc_adm_access_t *adm_access,
                 const char *from,
                 const char *to,
                 svn_boolean_t recurse,
                 svn_wc_relocation_validator2_t validator,
                 void *validator_baton,
                 apr_pool_t *pool)
{
  struct compat2_baton cb;

  cb.validator = validator;
  cb.baton = validator_baton;

  return svn_wc_relocate3(path, adm_access, from, to, recurse,
                          compat2_validator, &cb, pool);
}