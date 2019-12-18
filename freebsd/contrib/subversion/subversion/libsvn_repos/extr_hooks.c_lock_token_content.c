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
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_temp_file (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_path_uri_autoescape (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf__morph_into_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_appendcstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_stringbuf_appendstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_stringbuf_create (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_createf (int /*<<< orphan*/ *,char*,char const*,char const*) ; 

__attribute__((used)) static svn_error_t *
lock_token_content(apr_file_t **handle, apr_hash_t *lock_tokens,
                   apr_pool_t *pool)
{
  svn_stringbuf_t *lock_str = svn_stringbuf_create("LOCK-TOKENS:\n", pool);
  apr_hash_index_t *hi;

  for (hi = apr_hash_first(pool, lock_tokens); hi;
       hi = apr_hash_next(hi))
    {
      const char *token = apr_hash_this_key(hi);
      const char *path = apr_hash_this_val(hi);

      if (path == (const char *) 1)
        {
          /* Special handling for svn_fs_access_t * created by using deprecated
             svn_fs_access_add_lock_token() function. */
          path = "";
        }
      else
        {
          path = svn_path_uri_autoescape(path, pool);
        }

      svn_stringbuf_appendstr(lock_str,
          svn_stringbuf_createf(pool, "%s|%s\n", path, token));
    }

  svn_stringbuf_appendcstr(lock_str, "\n");
  return create_temp_file(handle,
                          svn_stringbuf__morph_into_string(lock_str), pool);
}