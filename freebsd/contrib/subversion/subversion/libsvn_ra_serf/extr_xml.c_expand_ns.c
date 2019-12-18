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
struct TYPE_5__ {char* url; int /*<<< orphan*/ * xmlns; struct TYPE_5__* next; } ;
typedef  TYPE_1__ svn_ra_serf__ns_t ;
struct TYPE_6__ {char* xmlns; char const* name; } ;
typedef  TYPE_2__ svn_ra_serf__dav_props_t ;

/* Variables and functions */
 char* strchr (char const*,char) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static void
expand_ns(svn_ra_serf__dav_props_t *returned_prop_name,
                       const svn_ra_serf__ns_t *ns_list,
                       const char *name)
{
  const char *colon;

  colon = strchr(name, ':');
  if (colon)
    {
      const svn_ra_serf__ns_t *ns;

      for (ns = ns_list; ns; ns = ns->next)
        {
          if (strncmp(ns->xmlns, name, colon - name) == 0)
            {
              returned_prop_name->xmlns = ns->url;
              returned_prop_name->name = colon + 1;
              return;
            }
        }
    }
  else
    {
      const svn_ra_serf__ns_t *ns;

      for (ns = ns_list; ns; ns = ns->next)
        {
          if (! ns->xmlns[0])
            {
              returned_prop_name->xmlns = ns->url;
              returned_prop_name->name = name;
              return;
            }
        }
    }

  /* If the prefix is not found, then the name is NOT within a
     namespace.  */
  returned_prop_name->xmlns = "";
  returned_prop_name->name = name;
}