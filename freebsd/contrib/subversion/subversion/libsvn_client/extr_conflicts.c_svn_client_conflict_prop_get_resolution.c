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
struct TYPE_3__ {int /*<<< orphan*/  resolved_props; } ;
typedef  TYPE_1__ svn_client_conflict_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_option_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_option_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_client_conflict_option_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_option_unspecified ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 

svn_client_conflict_option_id_t
svn_client_conflict_prop_get_resolution(svn_client_conflict_t *conflict,
                                        const char *propname)
{
  svn_client_conflict_option_t *option;

  option = svn_hash_gets(conflict->resolved_props, propname);
  if (option == NULL)
    return svn_client_conflict_option_unspecified;

  return svn_client_conflict_option_get_id(option);
}