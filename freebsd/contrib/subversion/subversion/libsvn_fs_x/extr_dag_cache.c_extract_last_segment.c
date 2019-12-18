#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
struct TYPE_4__ {scalar_t__ len; char* data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  svn_stringbuf_setempty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_boolean_t
extract_last_segment(const svn_string_t *path,
                     svn_string_t *directory,
                     svn_stringbuf_t *entry)
{
  const char *segment_start;
  const char *parent_end;

  /* Edge case.  We can't navigate in empty paths. */
  if (path->len == 0)
    return FALSE;

  /* Find the start of the last segment.  Note that normalized paths never
     start nor end with a '/'. */
  segment_start = path->data + path->len - 1;
  while (*segment_start != '/' && segment_start != path->data)
    --segment_start;

  /* At root level already, i.e. no parent? */
  if (segment_start == path->data)
    {
      /* Construct result. */
      directory->data = "";
      directory->len = 0;

      svn_stringbuf_setempty(entry);
      svn_stringbuf_appendbytes(entry, path->data, path->len);

      return TRUE;
    }

  /* Find the end of the parent directory. */
  parent_end = segment_start;
  while (parent_end[-1] == '/')
    --parent_end;

  /* Construct result. */
  directory->data = path->data;
  directory->len = parent_end - path->data;

  ++segment_start; /* previously pointed to the last '/'. */
  svn_stringbuf_setempty(entry);
  svn_stringbuf_appendbytes(entry, segment_start,
                            path->len - (segment_start - path->data));

  return TRUE;
}