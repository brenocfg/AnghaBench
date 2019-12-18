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
 size_t dirent_root_length (char const*,size_t) ; 

__attribute__((used)) static apr_size_t
dirent_previous_segment(const char *dirent,
                        apr_size_t len)
{
  if (len == 0)
    return 0;

  --len;
  while (len > 0 && dirent[len] != '/'
#ifdef SVN_USE_DOS_PATHS
                 && (dirent[len] != ':' || len != 1)
#endif /* SVN_USE_DOS_PATHS */
        )
    --len;

  /* check if the remaining segment including trailing '/' is a root dirent */
  if (dirent_root_length(dirent, len+1) == len + 1)
    return len + 1;
  else
    return len;
}