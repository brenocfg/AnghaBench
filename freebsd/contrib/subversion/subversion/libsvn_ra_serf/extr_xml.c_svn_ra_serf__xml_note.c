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
struct TYPE_4__ {int state; int /*<<< orphan*/  state_pool; int /*<<< orphan*/ * attrs; struct TYPE_4__* prev; } ;
typedef  TYPE_1__ svn_ra_serf__xml_estate_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ensure_pool (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
svn_ra_serf__xml_note(svn_ra_serf__xml_estate_t *xes,
                      int state,
                      const char *name,
                      const char *value)
{
  svn_ra_serf__xml_estate_t *scan;

  for (scan = xes; scan != NULL && scan->state != state; scan = scan->prev)
    /* pass */ ;

  SVN_ERR_ASSERT_NO_RETURN(scan != NULL);

  /* Make sure the target state has a pool.  */
  ensure_pool(scan);

  /* ... and attribute storage.  */
  if (scan->attrs == NULL)
    scan->attrs = apr_hash_make(scan->state_pool);

  /* In all likelihood, NAME is a string constant. But we can't really
     be sure. And it isn't like we're storing a billion of these into
     the state pool.  */
  svn_hash_sets(scan->attrs,
                apr_pstrdup(scan->state_pool, name),
                apr_pstrdup(scan->state_pool, value));
}