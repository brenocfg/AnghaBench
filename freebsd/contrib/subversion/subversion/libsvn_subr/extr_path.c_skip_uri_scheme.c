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

__attribute__((used)) static const char *
skip_uri_scheme(const char *path)
{
  apr_size_t j;

  /* A scheme is terminated by a : and cannot contain any /'s. */
  for (j = 0; path[j] && path[j] != ':'; ++j)
    if (path[j] == '/')
      return NULL;

  if (j > 0 && path[j] == ':' && path[j+1] == '/' && path[j+2] == '/')
    return path + j + 3;

  return NULL;
}