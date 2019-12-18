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
struct TYPE_4__ {int len; char* data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  size_t apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 char canonicalize_to_lower (char) ; 

svn_boolean_t
svn_cert__match_dns_identity(svn_string_t *pattern, svn_string_t *hostname)
{
  apr_size_t pattern_pos = 0, hostname_pos = 0;

  /* support leading wildcards that composed of the only character in the
   * left-most label. */
  if (pattern->len >= 2 &&
      pattern->data[pattern_pos] == '*' &&
      pattern->data[pattern_pos + 1] == '.')
    {
      while (hostname_pos < hostname->len &&
             hostname->data[hostname_pos] != '.')
        {
          hostname_pos++;
        }
      /* Assume that the wildcard must match something.  Rule 2 says
       * that *.example.com should not match example.com.  If the wildcard
       * ends up not matching anything then it matches .example.com which
       * seems to be essentially the same as just example.com */
      if (hostname_pos == 0)
        return FALSE;

      pattern_pos++;
    }

  while (pattern_pos < pattern->len && hostname_pos < hostname->len)
    {
      char pattern_c = pattern->data[pattern_pos];
      char hostname_c = hostname->data[hostname_pos];

      /* fold case as described in RFC 4343.
       * Note: We actually convert to lowercase, since our URI
       * canonicalization code converts to lowercase and generally
       * most certs are issued with lowercase DNS names, meaning
       * this avoids the fold operation in most cases.  The RFC
       * suggests the opposite transformation, but doesn't require
       * any specific implementation in any case.  It is critical
       * that this folding be locale independent so you can't use
       * tolower(). */
      pattern_c = canonicalize_to_lower(pattern_c);
      hostname_c = canonicalize_to_lower(hostname_c);

      if (pattern_c != hostname_c)
        {
          /* doesn't match */
          return FALSE;
        }
      else
        {
          /* characters match so skip both */
          pattern_pos++;
          hostname_pos++;
        }
    }

  /* ignore a trailing period on the hostname since this has no effect on the
   * security of the matching.  See the following for the long explanation as
   * to why:
   * https://bugzilla.mozilla.org/show_bug.cgi?id=134402#c28
   */
  if (pattern_pos == pattern->len &&
      hostname_pos == hostname->len - 1 &&
      hostname->data[hostname_pos] == '.')
    hostname_pos++;

  if (pattern_pos != pattern->len || hostname_pos != hostname->len)
    {
      /* end didn't match */
      return FALSE;
    }

  return TRUE;
}