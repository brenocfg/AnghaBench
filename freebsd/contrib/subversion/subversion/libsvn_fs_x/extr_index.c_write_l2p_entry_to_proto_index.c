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
struct TYPE_3__ {int /*<<< orphan*/  sub_item; int /*<<< orphan*/  item_index; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ l2p_proto_entry_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  write_uint64_to_proto_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
write_l2p_entry_to_proto_index(apr_file_t *proto_index,
                               l2p_proto_entry_t entry,
                               apr_pool_t *scratch_pool)
{
  SVN_ERR(write_uint64_to_proto_index(proto_index, entry.offset,
                                      scratch_pool));
  SVN_ERR(write_uint64_to_proto_index(proto_index, entry.item_index,
                                      scratch_pool));
  SVN_ERR(write_uint64_to_proto_index(proto_index, entry.sub_item,
                                      scratch_pool));

  return SVN_NO_ERROR;
}