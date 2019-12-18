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
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_canonical (char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

int
svn_path_compare_paths(const char *path1,
                       const char *path2)
{
  apr_size_t path1_len = strlen(path1);
  apr_size_t path2_len = strlen(path2);
  apr_size_t min_len = ((path1_len < path2_len) ? path1_len : path2_len);
  apr_size_t i = 0;

  assert(is_canonical(path1, path1_len));
  assert(is_canonical(path2, path2_len));

  /* Skip past common prefix. */
  while (i < min_len && path1[i] == path2[i])
    ++i;

  /* Are the paths exactly the same? */
  if ((path1_len == path2_len) && (i >= min_len))
    return 0;

  /* Children of paths are greater than their parents, but less than
     greater siblings of their parents. */
  if ((path1[i] == '/') && (path2[i] == 0))
    return 1;
  if ((path2[i] == '/') && (path1[i] == 0))
    return -1;
  if (path1[i] == '/')
    return -1;
  if (path2[i] == '/')
    return 1;

  /* Common prefix was skipped above, next character is compared to
     determine order.  We need to use an unsigned comparison, though,
     so a "next character" of NULL (0x00) sorts numerically
     smallest. */
  return (unsigned char)(path1[i]) < (unsigned char)(path2[i]) ? -1 : 1;
}