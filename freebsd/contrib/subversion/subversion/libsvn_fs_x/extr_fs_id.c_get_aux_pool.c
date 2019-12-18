#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * aux_pool; int /*<<< orphan*/  owner; } ;
typedef  TYPE_2__ svn_fs_x__id_context_t ;
struct TYPE_5__ {TYPE_2__* fsap_data; } ;
struct TYPE_7__ {TYPE_1__ generic_id; } ;
typedef  TYPE_3__ fs_x__id_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 

__attribute__((used)) static apr_pool_t *
get_aux_pool(const fs_x__id_t *id)
{
  svn_fs_x__id_context_t *context = id->generic_id.fsap_data;
  if (!context->aux_pool)
    context->aux_pool = svn_pool_create(context->owner);

  return context->aux_pool;
}