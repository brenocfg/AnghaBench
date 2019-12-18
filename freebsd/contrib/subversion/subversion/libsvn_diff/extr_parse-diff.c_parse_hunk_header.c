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
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
struct TYPE_8__ {int /*<<< orphan*/  modified_length; int /*<<< orphan*/  modified_start; int /*<<< orphan*/  original_length; int /*<<< orphan*/  original_start; } ;
typedef  TYPE_2__ svn_diff_hunk_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  parse_range (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  starts_with (char const*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (TYPE_1__*,char const*,int) ; 
 TYPE_1__* svn_stringbuf_create_ensure (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_setempty (TYPE_1__*) ; 

__attribute__((used)) static svn_boolean_t
parse_hunk_header(const char *header, svn_diff_hunk_t *hunk,
                  const char *atat, apr_pool_t *pool)
{
  const char *p;
  const char *start;
  svn_stringbuf_t *range;

  p = header + strlen(atat);
  if (*p != ' ')
    /* No. */
    return FALSE;
  p++;
  if (*p != '-')
    /* Nah... */
    return FALSE;
  /* OK, this may be worth allocating some memory for... */
  range = svn_stringbuf_create_ensure(31, pool);
  start = ++p;
  while (*p && *p != ' ')
    {
      p++;
    }

  if (*p != ' ')
    /* No no no... */
    return FALSE;

  svn_stringbuf_appendbytes(range, start, p - start);

  /* Try to parse the first range. */
  if (! parse_range(&hunk->original_start, &hunk->original_length, range->data))
    return FALSE;

  /* Clear the stringbuf so we can reuse it for the second range. */
  svn_stringbuf_setempty(range);
  p++;
  if (*p != '+')
    /* Eeek! */
    return FALSE;
  /* OK, this may be worth copying... */
  start = ++p;
  while (*p && *p != ' ')
    {
      p++;
    }
  if (*p != ' ')
    /* No no no... */
    return FALSE;

  svn_stringbuf_appendbytes(range, start, p - start);

  /* Check for trailing @@ */
  p++;
  if (! starts_with(p, atat))
    return FALSE;

  /* There may be stuff like C-function names after the trailing @@,
   * but we ignore that. */

  /* Try to parse the second range. */
  if (! parse_range(&hunk->modified_start, &hunk->modified_length, range->data))
    return FALSE;

  /* Hunk header is good. */
  return TRUE;
}