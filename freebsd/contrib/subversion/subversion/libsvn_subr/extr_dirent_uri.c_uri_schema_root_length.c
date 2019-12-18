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
 scalar_t__ strncmp (char*,char const*,int) ; 

__attribute__((used)) static apr_size_t
uri_schema_root_length(const char *uri, apr_size_t len)
{
  apr_size_t i;

  for (i = 0; i < len; i++)
    {
      if (uri[i] == '/')
        {
          if (i > 0 && uri[i-1] == ':' && i < len-1 && uri[i+1] == '/')
            {
              /* We have an absolute uri */
              if (i == 5 && strncmp("file", uri, 4) == 0)
                return 7; /* file:// */
              else
                {
                  for (i += 2; i < len; i++)
                    if (uri[i] == '/')
                      return i;

                  return len; /* Only a hostname is found */
                }
            }
          else
            return 0;
        }
    }

  return 0;
}