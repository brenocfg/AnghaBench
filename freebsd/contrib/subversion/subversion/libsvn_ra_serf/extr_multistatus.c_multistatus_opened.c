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
typedef  int /*<<< orphan*/  svn_ra_serf__xml_estate_t ;
struct TYPE_3__ {char* name; int /*<<< orphan*/  xmlns; } ;
typedef  TYPE_1__ svn_ra_serf__dav_props_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  MS_PROPSTAT ; 
#define  MS_PROPSTAT_PROP_NAME 129 
 int /*<<< orphan*/  SVN_DAV_PROP_NS_SVN ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_PREFIX ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
#define  S_ERROR 128 
 char* apr_pstrcat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__xml_note (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static svn_error_t *
multistatus_opened(svn_ra_serf__xml_estate_t *xes,
                   void *baton,
                   int entered_state,
                   const svn_ra_serf__dav_props_t *tag,
                   apr_pool_t *scratch_pool)
{
  /*struct svn_ra_serf__server_error_t *server_error = baton;*/
  const char *propname;

  switch (entered_state)
    {
      case MS_PROPSTAT_PROP_NAME:
        if (strcmp(tag->xmlns, SVN_DAV_PROP_NS_SVN) == 0)
          propname = apr_pstrcat(scratch_pool, SVN_PROP_PREFIX, tag->name,
                                 SVN_VA_NULL);
        else
          propname = tag->name;
        svn_ra_serf__xml_note(xes, MS_PROPSTAT, "propname", propname);
        break;
      case S_ERROR:
        /* This toggles an has error boolean in libsvn_ra_neon in 1.7 */
        break;
    }

  return SVN_NO_ERROR;
}