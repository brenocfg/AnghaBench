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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ l2p_proto_entry_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_l2p_entry_to_proto_index (int /*<<< orphan*/ *,TYPE_1__,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__l2p_proto_index_add_revision(apr_file_t *proto_index,
                                       apr_pool_t *scratch_pool)
{
  l2p_proto_entry_t entry = { 0 };
  return svn_error_trace(write_l2p_entry_to_proto_index(proto_index, entry,
                                                        scratch_pool));
}