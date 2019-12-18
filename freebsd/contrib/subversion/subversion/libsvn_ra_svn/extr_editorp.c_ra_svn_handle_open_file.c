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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__list_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_10__ {int /*<<< orphan*/  baton; } ;
typedef  TYPE_2__ ra_svn_token_entry_t ;
struct TYPE_11__ {int /*<<< orphan*/  file_pool; TYPE_1__* editor; int /*<<< orphan*/  file_refs; } ;
typedef  TYPE_3__ ra_svn_driver_state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* open_file ) (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_CMD_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lookup_token (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__**) ; 
 TYPE_2__* store_token (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__parse_tuple (int /*<<< orphan*/  const*,char*,char const**,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 char* svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_is_canonical (char const*) ; 

__attribute__((used)) static svn_error_t *
ra_svn_handle_open_file(svn_ra_svn_conn_t *conn,
                        apr_pool_t *pool,
                        const svn_ra_svn__list_t *params,
                        ra_svn_driver_state_t *ds)
{
  const char *path;
  svn_string_t *token, *file_token;
  svn_revnum_t rev;
  ra_svn_token_entry_t *entry, *file_entry;

  SVN_ERR(svn_ra_svn__parse_tuple(params, "css(?r)", &path, &token,
                                  &file_token, &rev));
  SVN_ERR(lookup_token(ds, token, FALSE, &entry));
  ds->file_refs++;

  /* The PATH should be canonical .. but never trust incoming data. */
  if (!svn_relpath_is_canonical(path))
    path = svn_relpath_canonicalize(path, pool);

  file_entry = store_token(ds, NULL, file_token, TRUE, ds->file_pool);
  SVN_CMD_ERR(ds->editor->open_file(path, entry->baton, rev, ds->file_pool,
                                    &file_entry->baton));
  return SVN_NO_ERROR;
}