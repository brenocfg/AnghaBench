#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* data; size_t len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  size_t apr_size_t ;

/* Variables and functions */

__attribute__((used)) static const char *
next_segment(svn_stringbuf_t *segment,
             const char *path)
{
  apr_size_t len;
  char c;

  /* Read and scan PATH for NUL and '/' -- whichever comes first. */
  for (len = 0, c = *path; c; c = path[++len])
    if (c == '/')
      {
        /* End of segment. */
        segment->data[len] = 0;
        segment->len = len;

        /* If PATH is not normalized, this is where we skip whole sequences
         * of separators. */
        while (path[++len] == '/')
          ;

        /* Continue behind the last separator in the sequence.  We will
         * treat trailing '/' as indicating an empty trailing segment.
         * Therefore, we never have to return NULL here. */
        return path + len;
      }
    else
      {
        /* Copy segment contents directly into the result buffer.
         * On many architectures, this is almost or entirely for free. */
        segment->data[len] = c;
      }

  /* No separator found, so all of PATH has been the last segment. */
  segment->data[len] = 0;
  segment->len = len;

  /* Tell the caller that this has been the last segment. */
  return NULL;
}