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
struct TYPE_5__ {scalar_t__ supports_deadprop_count; } ;
typedef  TYPE_1__ svn_ra_serf__session_t ;
struct TYPE_6__ {char* xmlns; char* name; } ;
typedef  TYPE_2__ svn_ra_serf__dav_props_t ;
typedef  int apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 char* SVN_DAV_PROP_NS_DAV ; 
 char* SVN_DAV__CREATIONDATE ; 
 char* SVN_DAV__VERSION_NAME ; 
 int SVN_DIRENT_CREATED_REV ; 
 int SVN_DIRENT_HAS_PROPS ; 
 int SVN_DIRENT_KIND ; 
 int SVN_DIRENT_LAST_AUTHOR ; 
 int SVN_DIRENT_SIZE ; 
 int SVN_DIRENT_TIME ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 TYPE_2__* apr_array_push (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_tristate_false ; 

apr_array_header_t *
svn_ra_serf__get_dirent_props(apr_uint32_t dirent_fields,
                              svn_ra_serf__session_t *session,
                              apr_pool_t *result_pool)
{
  svn_ra_serf__dav_props_t *prop;
  apr_array_header_t *props = apr_array_make
    (result_pool, 7, sizeof(svn_ra_serf__dav_props_t));

  if (session->supports_deadprop_count != svn_tristate_false
      || ! (dirent_fields & SVN_DIRENT_HAS_PROPS))
    {
      if (dirent_fields & SVN_DIRENT_KIND)
        {
          prop = apr_array_push(props);
          prop->xmlns = "DAV:";
          prop->name = "resourcetype";
        }

      if (dirent_fields & SVN_DIRENT_SIZE)
        {
          prop = apr_array_push(props);
          prop->xmlns = "DAV:";
          prop->name = "getcontentlength";
        }

      if (dirent_fields & SVN_DIRENT_HAS_PROPS)
        {
          prop = apr_array_push(props);
          prop->xmlns = SVN_DAV_PROP_NS_DAV;
          prop->name = "deadprop-count";
        }

      if (dirent_fields & SVN_DIRENT_CREATED_REV)
        {
          svn_ra_serf__dav_props_t *p = apr_array_push(props);
          p->xmlns = "DAV:";
          p->name = SVN_DAV__VERSION_NAME;
        }

      if (dirent_fields & SVN_DIRENT_TIME)
        {
          prop = apr_array_push(props);
          prop->xmlns = "DAV:";
          prop->name = SVN_DAV__CREATIONDATE;
        }

      if (dirent_fields & SVN_DIRENT_LAST_AUTHOR)
        {
          prop = apr_array_push(props);
          prop->xmlns = "DAV:";
          prop->name = "creator-displayname";
        }
    }
  else
    {
      /* We found an old subversion server that can't handle
         the deadprop-count property in the way we expect.

         The neon behavior is to retrieve all properties in this case */
      prop = apr_array_push(props);
      prop->xmlns = "DAV:";
      prop->name = "allprop";
    }

  return props;
}