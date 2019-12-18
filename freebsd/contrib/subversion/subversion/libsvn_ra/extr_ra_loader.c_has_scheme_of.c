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
typedef  size_t apr_size_t ;

/* Variables and functions */
 size_t strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,size_t) ; 

__attribute__((used)) static const char *
has_scheme_of(const char * const *schemes, const char *url)
{
  apr_size_t len;

  for ( ; *schemes != NULL; ++schemes)
    {
      const char *scheme = *schemes;
      len = strlen(scheme);
      /* Case-insensitive comparison, per RFC 2396 section 3.1.  Allow
         URL to contain a trailing "+foo" section in the scheme, since
         that's how we specify tunnel schemes in ra_svn. */
      if (strncasecmp(scheme, url, len) == 0 &&
          (url[len] == ':' || url[len] == '+'))
        return scheme;
    }

  return NULL;
}