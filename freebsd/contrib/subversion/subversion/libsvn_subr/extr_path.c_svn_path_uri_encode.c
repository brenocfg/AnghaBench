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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_uri__char_validity ; 
 char* uri_escape (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

const char *
svn_path_uri_encode(const char *path, apr_pool_t *pool)
{
  const char *ret;

  ret = uri_escape(path, svn_uri__char_validity, pool);

  /* Our interface guarantees a copy. */
  if (ret == path)
    return apr_pstrdup(pool, path);
  else
    return ret;
}