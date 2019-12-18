#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* new_data; TYPE_3__* ops; } ;
typedef  TYPE_2__ svn_txdelta_window_t ;
struct TYPE_10__ {size_t const length; scalar_t__ action_code; int offset; } ;
typedef  TYPE_3__ svn_txdelta_op_t ;
typedef  int /*<<< orphan*/  svn_txdelta__ops_baton_t ;
struct TYPE_11__ {size_t* offs; } ;
typedef  TYPE_4__ offset_index_t ;
typedef  size_t apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_8__ {char* data; } ;

/* Variables and functions */
 size_t MIN (size_t,size_t const) ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t search_offset_index (TYPE_4__ const*,size_t,size_t) ; 
 int /*<<< orphan*/  svn_txdelta__insert_op (int /*<<< orphan*/ *,scalar_t__,size_t,size_t const,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_txdelta_new ; 
 scalar_t__ svn_txdelta_target ; 

__attribute__((used)) static void
copy_source_ops(apr_size_t offset, apr_size_t limit,
                apr_size_t target_offset,
                apr_size_t hint,
                svn_txdelta__ops_baton_t *build_baton,
                const svn_txdelta_window_t *window,
                const offset_index_t *ndx,
                apr_pool_t *pool)
{
  apr_size_t op_ndx = search_offset_index(ndx, offset, hint);
  for (;; ++op_ndx)
    {
      const svn_txdelta_op_t *const op = &window->ops[op_ndx];
      const apr_size_t *const off = &ndx->offs[op_ndx];
      const apr_size_t fix_offset = (offset > off[0] ? offset - off[0] : 0);
      const apr_size_t fix_limit = (off[0] >= limit ? 0
                                    : (off[1] > limit ? off[1] - limit : 0));

      /* Ideally, we'd do this check before assigning fix_offset and
         fix_limit; but then we couldn't make them const whilst still
         adhering to C90 rules. Instead, we're going to assume that a
         smart optimizing compiler will reorder this check before the
         local variable initialization. */
      if (off[0] >= limit)
          break;

      /* It would be extremely weird if the fixed-up op had zero length. */
      assert(fix_offset + fix_limit < op->length);

      if (op->action_code != svn_txdelta_target)
        {
          /* Delta ops that don't depend on the virtual target can be
             copied to the composite unchanged. */
          const char *const new_data = (op->action_code == svn_txdelta_new
                                        ? (window->new_data->data
                                           + op->offset + fix_offset)
                                        : NULL);

          svn_txdelta__insert_op(build_baton, op->action_code,
                                 op->offset + fix_offset,
                                 op->length - fix_offset - fix_limit,
                                 new_data, pool);
        }
      else
        {
          /* The source of a target copy must start before the current
             offset in the (virtual) target stream. */
          assert(op->offset < off[0]);

          if (op->offset + op->length - fix_limit <= off[0])
            {
              /* The recursion _must_ end, otherwise the delta has
                 circular references, and that is not possible. */
              copy_source_ops(op->offset + fix_offset,
                              op->offset + op->length - fix_limit,
                              target_offset,
                              op_ndx,
                              build_baton, window, ndx, pool);
            }
          else
            {
              /* This is an overlapping target copy.
                 The idea here is to transpose the pattern, then generate
                 another overlapping copy. */
              const apr_size_t ptn_length = off[0] - op->offset;
              const apr_size_t ptn_overlap = fix_offset % ptn_length;
              apr_size_t fix_off = fix_offset;
              apr_size_t tgt_off = target_offset;
              assert(ptn_length > ptn_overlap);

              /* Unconditionally issue the second subrange of the
                 pattern. This is always correct, since the outer
                 condition already verifies that there is an overlap
                 in the target copy. */
              {
                const apr_size_t length =
                  MIN(op->length - fix_off - fix_limit,
                      ptn_length - ptn_overlap);
                copy_source_ops(op->offset + ptn_overlap,
                                op->offset + ptn_overlap + length,
                                tgt_off,
                                op_ndx,
                                build_baton, window, ndx, pool);
                fix_off += length;
                tgt_off += length;
              }

              assert(fix_off + fix_limit <= op->length);
              if (ptn_overlap > 0
                  && fix_off + fix_limit < op->length)
                {
                  /* Issue the first subrange in the pattern. */
                  const apr_size_t length =
                    MIN(op->length - fix_off - fix_limit, ptn_overlap);
                  copy_source_ops(op->offset,
                                  op->offset + length,
                                  tgt_off,
                                  op_ndx,
                                  build_baton, window, ndx, pool);
                  fix_off += length;
                  tgt_off += length;
                }

              assert(fix_off + fix_limit <= op->length);
              if (fix_off + fix_limit < op->length)
                {
                  /* Now multiply the pattern */
                  svn_txdelta__insert_op(build_baton, svn_txdelta_target,
                                         tgt_off - ptn_length,
                                         op->length - fix_off - fix_limit,
                                         NULL, pool);
                }
            }
        }

      /* Adjust the target offset for the next op in the list. */
      target_offset += op->length - fix_offset - fix_limit;
    }
}