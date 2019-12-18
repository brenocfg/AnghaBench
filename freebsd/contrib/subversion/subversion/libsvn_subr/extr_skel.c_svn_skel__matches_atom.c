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
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  data; scalar_t__ is_atom; } ;
typedef  TYPE_1__ svn_skel_t ;
typedef  int svn_boolean_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

svn_boolean_t
svn_skel__matches_atom(const svn_skel_t *skel, const char *str)
{
  if (skel && skel->is_atom)
    {
      apr_size_t len = strlen(str);

      return (skel->len == len
              && ! memcmp(skel->data, str, len));
    }
  return FALSE;
}