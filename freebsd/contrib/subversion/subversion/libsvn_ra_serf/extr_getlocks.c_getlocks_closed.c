#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__xml_estate_t ;
struct TYPE_9__ {char const* path; char const* token; int /*<<< orphan*/  expiration_date; int /*<<< orphan*/  creation_date; void* comment; void* owner; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ svn_lock_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_10__ {scalar_t__ requested_depth; int /*<<< orphan*/  hash; int /*<<< orphan*/  pool; int /*<<< orphan*/  path; } ;
typedef  TYPE_3__ lock_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int COMMENT ; 
 int CREATION_DATE ; 
 int EXPIRATION_DATE ; 
 scalar_t__ FALSE ; 
 int LOCK ; 
 int OWNER ; 
 int PATH ; 
 char* SVN_DAV__CREATIONDATE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int TOKEN ; 
 scalar_t__ TRUE ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_depth_files ; 
 scalar_t__ svn_depth_immediates ; 
 scalar_t__ svn_depth_infinity ; 
 char* svn_fspath__skip_ancestor (int /*<<< orphan*/ ,char const*) ; 
 void* svn_hash_gets (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,char const*,TYPE_2__*) ; 
 TYPE_2__* svn_lock_dup (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int svn_path_component_count (char const*) ; 
 int /*<<< orphan*/  svn_ra_serf__xml_note (int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_time_from_cstring (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
getlocks_closed(svn_ra_serf__xml_estate_t *xes,
                void *baton,
                int leaving_state,
                const svn_string_t *cdata,
                apr_hash_t *attrs,
                apr_pool_t *scratch_pool)
{
  lock_context_t *lock_ctx = baton;

  if (leaving_state == LOCK)
    {
      const char *path = svn_hash_gets(attrs, "path");
      const char *token = svn_hash_gets(attrs, "token");
      svn_boolean_t save_lock = FALSE;

      /* Filter out unwanted paths.  Since Subversion only allows
         locks on files, we can treat depth=immediates the same as
         depth=files for filtering purposes.  Meaning, we'll keep
         this lock if:

         a) its path is the very path we queried, or
         b) we've asked for a fully recursive answer, or
         c) we've asked for depth=files or depth=immediates, and this
            lock is on an immediate child of our query path.
      */
      if (! token)
        {
          /* A lock without a token is not a lock; just an answer that there
             is no lock on the node. */
          save_lock = FALSE;
        }
      if (strcmp(lock_ctx->path, path) == 0
          || lock_ctx->requested_depth == svn_depth_infinity)
        {
          save_lock = TRUE;
        }
      else if (lock_ctx->requested_depth == svn_depth_files
               || lock_ctx->requested_depth == svn_depth_immediates)
        {
          const char *relpath = svn_fspath__skip_ancestor(lock_ctx->path,
                                                          path);
          if (relpath && (svn_path_component_count(relpath) == 1))
            save_lock = TRUE;
        }

      if (save_lock)
        {
          /* We get to put the structure on the stack rather than using
             svn_lock_create(). Bwahahaha....   */
          svn_lock_t lock = { 0 };
          const char *date;
          svn_lock_t *result_lock;

          /* Note: these "attributes" came from child elements. Some of
             them may have not been sent, so the value will be NULL.  */

          lock.path = path;
          lock.token = token;
          lock.owner = svn_hash_gets(attrs, "owner");
          lock.comment = svn_hash_gets(attrs, "comment");

          date = svn_hash_gets(attrs, SVN_DAV__CREATIONDATE);
          if (date)
            SVN_ERR(svn_time_from_cstring(&lock.creation_date, date,
                                          scratch_pool));

          date = svn_hash_gets(attrs, "expirationdate");
          if (date)
            SVN_ERR(svn_time_from_cstring(&lock.expiration_date, date,
                                          scratch_pool));

          result_lock = svn_lock_dup(&lock, lock_ctx->pool);
          svn_hash_sets(lock_ctx->hash, result_lock->path, result_lock);
        }
    }
  else
    {
      const char *name;

      SVN_ERR_ASSERT(cdata != NULL);

      if (leaving_state == PATH)
        name = "path";
      else if (leaving_state == TOKEN)
        name = "token";
      else if (leaving_state == OWNER)
        name = "owner";
      else if (leaving_state == COMMENT)
        name = "comment";
      else if (leaving_state == CREATION_DATE)
        name = SVN_DAV__CREATIONDATE;
      else if (leaving_state == EXPIRATION_DATE)
        name = "expirationdate";
      else
        SVN_ERR_MALFUNCTION();

      /* Store the lock information onto the LOCK elemstate.  */
      svn_ra_serf__xml_note(xes, LOCK, name, cdata->data);
    }

  return SVN_NO_ERROR;
}