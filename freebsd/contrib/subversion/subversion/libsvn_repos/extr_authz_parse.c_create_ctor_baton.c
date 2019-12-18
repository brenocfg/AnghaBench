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
typedef  int /*<<< orphan*/  parsed_acl_t ;
struct TYPE_5__ {int /*<<< orphan*/ * parser_pool; int /*<<< orphan*/  rule_string_buffer; int /*<<< orphan*/  rule_path_buffer; int /*<<< orphan*/ * current_acl; int /*<<< orphan*/  parsed_acls; void* parsed_aliases; void* parsed_groups; void* parsed_rules; void* in_aliases; void* in_groups; void* parsing_groups; int /*<<< orphan*/ * section; void* sections; void* strings; TYPE_2__* authz; } ;
typedef  TYPE_1__ ctor_baton_t ;
struct TYPE_6__ {int /*<<< orphan*/ * pool; void* user_rights; int /*<<< orphan*/  authn_rights; int /*<<< orphan*/  anon_rights; } ;
typedef  TYPE_2__ authz_full_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  anon_access_token ; 
 int /*<<< orphan*/  apr_array_make (int /*<<< orphan*/ * const,int,int) ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  authn_access_token ; 
 int /*<<< orphan*/  init_global_rights (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_default_acl (TYPE_1__* const) ; 
 void* svn_hash__make (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  svn_membuf__create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_create_empty (int /*<<< orphan*/ * const) ; 

__attribute__((used)) static ctor_baton_t *
create_ctor_baton(apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  apr_pool_t *const parser_pool = svn_pool_create(scratch_pool);
  ctor_baton_t *const cb = apr_pcalloc(parser_pool, sizeof(*cb));

  authz_full_t *const authz = apr_pcalloc(result_pool, sizeof(*authz));
  init_global_rights(&authz->anon_rights, anon_access_token, result_pool);
  init_global_rights(&authz->authn_rights, authn_access_token, result_pool);
  authz->user_rights = svn_hash__make(result_pool);
  authz->pool = result_pool;

  cb->authz = authz;
  cb->strings = svn_hash__make(parser_pool);

  cb->sections = svn_hash__make(parser_pool);
  cb->section = NULL;
  cb->parsing_groups = FALSE;
  cb->in_groups = FALSE;
  cb->in_aliases = FALSE;

  cb->parsed_rules = svn_hash__make(parser_pool);
  cb->parsed_groups = svn_hash__make(parser_pool);
  cb->parsed_aliases = svn_hash__make(parser_pool);
  cb->parsed_acls = apr_array_make(parser_pool, 64, sizeof(parsed_acl_t));
  cb->current_acl = NULL;

  svn_membuf__create(&cb->rule_path_buffer, 0, parser_pool);
  cb->rule_string_buffer = svn_stringbuf_create_empty(parser_pool);

  cb->parser_pool = parser_pool;

  insert_default_acl(cb);

  return cb;
}