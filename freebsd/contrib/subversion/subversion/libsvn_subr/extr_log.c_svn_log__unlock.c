#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; scalar_t__ len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 char const* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 char* svn_path_uri_encode (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_appendcstr (TYPE_1__*,char*) ; 
 TYPE_1__* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 

const char *
svn_log__unlock(apr_hash_t *targets,
                svn_boolean_t break_lock, apr_pool_t *pool)
{
  apr_hash_index_t *hi;
  apr_pool_t *iterpool = svn_pool_create(pool);
  svn_stringbuf_t *space_separated_paths = svn_stringbuf_create_empty(pool);

  for (hi = apr_hash_first(pool, targets); hi; hi = apr_hash_next(hi))
    {
      const char *path = apr_hash_this_key(hi);
      svn_pool_clear(iterpool);
      if (space_separated_paths->len)
        svn_stringbuf_appendcstr(space_separated_paths, " ");
      svn_stringbuf_appendcstr(space_separated_paths,
                               svn_path_uri_encode(path, iterpool));
    }
  svn_pool_destroy(iterpool);

  return apr_psprintf(pool, "unlock (%s)%s", space_separated_paths->data,
                      break_lock ? " break" : "");
}