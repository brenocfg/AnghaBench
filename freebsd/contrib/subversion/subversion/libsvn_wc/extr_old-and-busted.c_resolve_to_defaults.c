#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ revision; scalar_t__ kind; int /*<<< orphan*/  url; } ;
typedef  TYPE_1__ svn_wc_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ENTRY_MISSING_REVISION ; 
 int /*<<< orphan*/  SVN_ERR_ENTRY_MISSING_URL ; 
 int /*<<< orphan*/  SVN_ERR_ENTRY_NOT_FOUND ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC_ENTRY_THIS_DIR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  take_from_entry (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
resolve_to_defaults(apr_hash_t *entries,
                    apr_pool_t *pool)
{
  apr_hash_index_t *hi;
  svn_wc_entry_t *default_entry
    = svn_hash_gets(entries, SVN_WC_ENTRY_THIS_DIR);

  /* First check the dir's own entry for consistency. */
  if (! default_entry)
    return svn_error_create(SVN_ERR_ENTRY_NOT_FOUND,
                            NULL,
                            _("Missing default entry"));

  if (default_entry->revision == SVN_INVALID_REVNUM)
    return svn_error_create(SVN_ERR_ENTRY_MISSING_REVISION,
                            NULL,
                            _("Default entry has no revision number"));

  if (! default_entry->url)
    return svn_error_create(SVN_ERR_ENTRY_MISSING_URL,
                            NULL,
                            _("Default entry is missing URL"));


  /* Then use it to fill in missing information in other entries. */
  for (hi = apr_hash_first(pool, entries); hi; hi = apr_hash_next(hi))
    {
      svn_wc_entry_t *this_entry = apr_hash_this_val(hi);

      if (this_entry == default_entry)
        /* THIS_DIR already has all the information it can possibly
           have.  */
        continue;

      if (this_entry->kind == svn_node_dir)
        /* Entries that are directories have everything but their
           name, kind, and state stored in the THIS_DIR entry of the
           directory itself.  However, we are disallowing the perusing
           of any entries outside of the current entries file.  If a
           caller wants more info about a directory, it should look in
           the entries file in the directory.  */
        continue;

      if (this_entry->kind == svn_node_file)
        /* For file nodes that do not explicitly have their ancestry
           stated, this can be derived from the default entry of the
           directory in which those files reside.  */
        take_from_entry(default_entry, this_entry, pool);
    }

  return SVN_NO_ERROR;
}