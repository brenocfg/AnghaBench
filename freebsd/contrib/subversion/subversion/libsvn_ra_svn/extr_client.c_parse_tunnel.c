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
 char* apr_pstrmemdup (int /*<<< orphan*/ *,char const*,int) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 

__attribute__((used)) static void parse_tunnel(const char *url, const char **tunnel,
                         apr_pool_t *pool)
{
  *tunnel = NULL;

  if (strncasecmp(url, "svn", 3) != 0)
    return;
  url += 3;

  /* Get the tunnel specification, if any. */
  if (*url == '+')
    {
      const char *p;

      url++;
      p = strchr(url, ':');
      if (!p)
        return;
      *tunnel = apr_pstrmemdup(pool, url, p - url);
    }
}