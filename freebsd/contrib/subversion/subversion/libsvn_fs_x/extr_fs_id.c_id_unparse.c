#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
struct TYPE_2__ {int /*<<< orphan*/  noderev_id; } ;
typedef  TYPE_1__ fs_x__id_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_fs_x__id_unparse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_string_t *
id_unparse(const svn_fs_id_t *fs_id,
           apr_pool_t *result_pool)
{
  const fs_x__id_t *id = (const fs_x__id_t *)fs_id;
  return svn_fs_x__id_unparse(&id->noderev_id, result_pool);
}