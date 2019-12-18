#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {scalar_t__ section; int /*<<< orphan*/  sections; int /*<<< orphan*/  parser_pool; scalar_t__ parsing_groups; int /*<<< orphan*/  current_acl; } ;
typedef  TYPE_2__ ctor_baton_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_AUTHZ_INVALID_CONFIG ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_hash_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_pstrmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interned_empty_string ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
check_open_section(ctor_baton_t *cb, svn_stringbuf_t *section)
{
  SVN_ERR_ASSERT(!cb->current_acl && !cb->section);
  if (apr_hash_get(cb->sections, section->data, section->len))
    {
      if (cb->parsing_groups)
        return svn_error_createf(
            SVN_ERR_AUTHZ_INVALID_CONFIG, NULL,
            _("Section appears more than once"
              " in the global groups file: [%s]"),
            section->data);
      else
        return svn_error_createf(
            SVN_ERR_AUTHZ_INVALID_CONFIG, NULL,
            _("Section appears more than once"
              " in the authz file: [%s]"),
            section->data);
    }

  cb->section = apr_pstrmemdup(cb->parser_pool, section->data, section->len);
  svn_hash_sets(cb->sections,  cb->section, interned_empty_string);
  return SVN_NO_ERROR;
}