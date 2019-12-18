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
struct TYPE_6__ {scalar_t__ action_code; scalar_t__ length; } ;
typedef  TYPE_2__ svn_txdelta_op_t ;
struct TYPE_7__ {int num_ops; TYPE_1__* new_data; TYPE_2__* ops; } ;
typedef  TYPE_3__ svn_txdelta__ops_baton_t ;
typedef  scalar_t__ apr_size_t ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 scalar_t__ svn_txdelta_new ; 
 scalar_t__ svn_txdelta_target ; 

apr_size_t
svn_txdelta__remove_copy(svn_txdelta__ops_baton_t *build_baton,
                         apr_size_t max_len)
{
  svn_txdelta_op_t *op;
  apr_size_t len = 0;

  /* remove ops back to front */
  while (build_baton->num_ops > 0)
    {
      op = &build_baton->ops[build_baton->num_ops-1];

      /*  we can't modify svn_txdelta_target ops -> stop there */
      if (op->action_code == svn_txdelta_target)
        break;

      /*  handle the case that we cannot remove the op entirely */
      if (op->length + len > max_len)
        {
          /* truncate only insertions. Copies don't benefit
             from being truncated. */
          if (op->action_code == svn_txdelta_new)
            {
               build_baton->new_data->len -= max_len - len;
               op->length -= max_len - len;
               len = max_len;
            }

          break;
        }

      /* drop the op entirely */
      if (op->action_code == svn_txdelta_new)
        build_baton->new_data->len -= op->length;

      len += op->length;
      --build_baton->num_ops;
    }

  return len;
}