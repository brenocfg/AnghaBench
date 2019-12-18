#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char const* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
struct TYPE_8__ {char* data; int len; } ;
typedef  TYPE_2__ svn_string_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_stringbuf_appendbytes (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  svn_stringbuf_setempty (TYPE_1__*) ; 

__attribute__((used)) static const char *
next_entry_name(svn_string_t *path,
                svn_stringbuf_t *entry)
{
  const char *segment_start;
  const char *segment_end;

  /* Moving to the next segment, skip separators
     (normalized does not imply canonical). */
  segment_start = path->data + path->len;
  while (*segment_start == '/')
    ++segment_start;

  /* End of path? */
  if (*segment_start == '\0')
    return NULL;

  /* Find the end of this segment.  Note that strchr would not give us the
     length of the last segment. */
  segment_end = segment_start;
  while (*segment_end != '/' && *segment_end != '\0')
    ++segment_end;

  /* Copy the segment into the result buffer. */
  svn_stringbuf_setempty(entry);
  svn_stringbuf_appendbytes(entry, segment_start,
                            segment_end - segment_start);

  /* Extend the "visible" part of the path to the end of that segment. */
  path->len = segment_end - path->data;

  /* Indicate that we found something. */
  return entry->data;
}