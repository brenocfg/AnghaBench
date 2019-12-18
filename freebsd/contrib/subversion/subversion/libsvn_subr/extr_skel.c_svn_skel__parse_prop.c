#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
struct TYPE_6__ {scalar_t__ len; TYPE_1__* next; int /*<<< orphan*/  data; struct TYPE_6__* children; } ;
typedef  TYPE_2__ svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; TYPE_2__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  is_valid_proplist_skel (TYPE_2__ const*) ; 
 int /*<<< orphan*/ * skel_err (char*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * svn_string_ncreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_skel__parse_prop(svn_string_t **propval,
                     const svn_skel_t *skel,
                     const char *propname,
                     apr_pool_t *pool /* result_pool */)
{
  svn_skel_t *elt;

  *propval = NULL;

  /* Validate the skel. */
  if (! is_valid_proplist_skel(skel))
    return skel_err("proplist");

  /* Look for PROPNAME in SKEL. */
  for (elt = skel->children; elt; elt = elt->next->next)
    {
      if (elt->len == strlen(propname)
          && strncmp(propname, elt->data, elt->len) == 0)
        {
          *propval = svn_string_ncreate(elt->next->data, elt->next->len,
                                        pool);
          break;
        }
      else
        {
          continue;
        }
    }
  return SVN_NO_ERROR;
}