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
struct TYPE_4__ {char const* data; int /*<<< orphan*/  len; int /*<<< orphan*/  is_atom; } ;
typedef  TYPE_1__ svn_skel_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

svn_skel_t *
svn_skel__str_atom(const char *str, apr_pool_t *pool)
{
  svn_skel_t *skel = apr_pcalloc(pool, sizeof(*skel));
  skel->is_atom = TRUE;
  skel->data = str;
  skel->len = strlen(str);

  return skel;
}