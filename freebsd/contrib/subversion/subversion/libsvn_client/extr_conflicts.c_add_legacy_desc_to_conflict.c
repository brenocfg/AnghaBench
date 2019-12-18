#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int kind; int /*<<< orphan*/  property_name; } ;
typedef  TYPE_1__ svn_wc_conflict_description2_t ;
struct TYPE_7__ {TYPE_1__ const* legacy_tree_conflict; int /*<<< orphan*/  legacy_prop_conflict_propname; int /*<<< orphan*/ * prop_conflicts; TYPE_1__ const* legacy_text_conflict; } ;
typedef  TYPE_2__ svn_client_conflict_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__ const*) ; 
#define  svn_wc_conflict_kind_property 130 
#define  svn_wc_conflict_kind_text 129 
#define  svn_wc_conflict_kind_tree 128 

__attribute__((used)) static void
add_legacy_desc_to_conflict(const svn_wc_conflict_description2_t *desc,
                            svn_client_conflict_t *conflict,
                            apr_pool_t *result_pool)
{
  switch (desc->kind)
    {
      case svn_wc_conflict_kind_text:
        conflict->legacy_text_conflict = desc;
        break;

      case svn_wc_conflict_kind_property:
        if (conflict->prop_conflicts == NULL)
          conflict->prop_conflicts = apr_hash_make(result_pool);
        svn_hash_sets(conflict->prop_conflicts, desc->property_name, desc);
        conflict->legacy_prop_conflict_propname = desc->property_name;
        break;

      case svn_wc_conflict_kind_tree:
        conflict->legacy_tree_conflict = desc;
        break;

      default:
        SVN_ERR_ASSERT_NO_RETURN(FALSE); /* unknown kind of conflict */
    }
}