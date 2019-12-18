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
struct TYPE_5__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_id_t ;
typedef  int svn_boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  node_id; } ;
typedef  TYPE_2__ id_private_t ;

/* Variables and functions */
 int TRUE ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_boolean_t
svn_fs_base__id_check_related(const svn_fs_id_t *a,
                              const svn_fs_id_t *b)
{
  id_private_t *pvta = a->fsap_data, *pvtb = b->fsap_data;

  if (a == b)
    return TRUE;

  return (strcmp(pvta->node_id, pvtb->node_id) == 0);
}