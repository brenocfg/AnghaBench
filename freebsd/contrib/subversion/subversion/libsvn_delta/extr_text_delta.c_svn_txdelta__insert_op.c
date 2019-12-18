#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int action_code; scalar_t__ offset; scalar_t__ length; } ;
typedef  TYPE_1__ svn_txdelta_op_t ;
struct TYPE_9__ {int num_ops; int ops_size; TYPE_4__* new_data; int /*<<< orphan*/  src_ops; TYPE_1__* ops; } ;
typedef  TYPE_2__ svn_txdelta__ops_baton_t ;
typedef  enum svn_delta_action { ____Placeholder_svn_delta_action } svn_delta_action ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_10__ {scalar_t__ len; } ;

/* Variables and functions */
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__* const,int) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (TYPE_4__*,char const*,scalar_t__) ; 
#define  svn_txdelta_new 130 
#define  svn_txdelta_source 129 
#define  svn_txdelta_target 128 

void
svn_txdelta__insert_op(svn_txdelta__ops_baton_t *build_baton,
                       enum svn_delta_action opcode,
                       apr_size_t offset,
                       apr_size_t length,
                       const char *new_data,
                       apr_pool_t *pool)
{
  svn_txdelta_op_t *op;

  /* Check if this op can be merged with the previous op. The delta
     combiner sometimes generates such ops, and this is the obvious
     place to make the check. */
  if (build_baton->num_ops > 0)
    {
      op = &build_baton->ops[build_baton->num_ops - 1];
      if (op->action_code == opcode
          && (opcode == svn_txdelta_new
              || op->offset + op->length == offset))
        {
          op->length += length;
          if (opcode == svn_txdelta_new)
            svn_stringbuf_appendbytes(build_baton->new_data,
                                      new_data, length);
          return;
        }
    }

  /* Create space for the new op. */
  if (build_baton->num_ops == build_baton->ops_size)
    {
      svn_txdelta_op_t *const old_ops = build_baton->ops;
      int const new_ops_size = (build_baton->ops_size == 0
                                ? 16 : 2 * build_baton->ops_size);
      build_baton->ops =
        apr_palloc(pool, new_ops_size * sizeof(*build_baton->ops));

      /* Copy any existing ops into the new array */
      if (old_ops)
        memcpy(build_baton->ops, old_ops,
               build_baton->ops_size * sizeof(*build_baton->ops));
      build_baton->ops_size = new_ops_size;
    }

  /* Insert the op. svn_delta_source and svn_delta_target are
     just inserted. For svn_delta_new, the new data must be
     copied into the window. */
  op = &build_baton->ops[build_baton->num_ops];
  switch (opcode)
    {
    case svn_txdelta_source:
      ++build_baton->src_ops;
      /*** FALLTHRU ***/
    case svn_txdelta_target:
      op->action_code = opcode;
      op->offset = offset;
      op->length = length;
      break;
    case svn_txdelta_new:
      op->action_code = opcode;
      op->offset = build_baton->new_data->len;
      op->length = length;
      svn_stringbuf_appendbytes(build_baton->new_data, new_data, length);
      break;
    default:
      assert(!"unknown delta op.");
    }

  ++build_baton->num_ops;
}