#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_serf__xml_estate_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  xmlns; } ;
typedef  TYPE_1__ svn_ra_serf__dav_props_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  ps_props; } ;
typedef  TYPE_2__ propfind_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int PROPSTAT ; 
 int PROPVAL ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__xml_note (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__xml_state_pool (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
propfind_opened(svn_ra_serf__xml_estate_t *xes,
                void *baton,
                int entered_state,
                const svn_ra_serf__dav_props_t *tag,
                apr_pool_t *scratch_pool)
{
  propfind_context_t *ctx = baton;

  if (entered_state == PROPVAL)
    {
        svn_ra_serf__xml_note(xes, PROPVAL, "ns", tag->xmlns);
      svn_ra_serf__xml_note(xes, PROPVAL, "name", tag->name);
    }
  else if (entered_state == PROPSTAT)
    {
      ctx->ps_props = apr_hash_make(svn_ra_serf__xml_state_pool(xes));
    }

  return SVN_NO_ERROR;
}