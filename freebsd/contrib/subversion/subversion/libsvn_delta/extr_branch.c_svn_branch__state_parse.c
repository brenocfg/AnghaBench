#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_element__payload_t ;
typedef  int /*<<< orphan*/  svn_element__content_t ;
struct TYPE_10__ {int /*<<< orphan*/  rev; } ;
typedef  TYPE_2__ svn_branch__txn_t ;
struct TYPE_11__ {TYPE_1__* priv; } ;
typedef  TYPE_3__ svn_branch__state_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_9__ {int /*<<< orphan*/  is_flat; int /*<<< orphan*/  history; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* branch_state_create (char*,int,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  branch_state_set_element (TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  history_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_branch_line (char*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_element_line (int*,int /*<<< orphan*/ *,int*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_element__content_create (int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_element__payload_create_ref (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_element__payload_create_subbranch (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
svn_branch__state_parse(svn_branch__state_t **new_branch,
                       svn_branch__txn_t *txn,
                       svn_stream_t *stream,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  char bid[1000];
  int root_eid, num_eids;
  svn_branch__state_t *branch_state;
  int i;

  SVN_ERR(parse_branch_line(bid, &root_eid, &num_eids,
                            stream, scratch_pool, scratch_pool));

  branch_state = branch_state_create(bid, root_eid, txn,
                                     result_pool);

  /* Read in the merge history. */
  SVN_ERR(history_parse(&branch_state->priv->history,
                        stream, result_pool, scratch_pool));

  /* Read in the structure. Set the payload of each normal element to a
     (branch-relative) reference. */
  for (i = 0; i < num_eids; i++)
    {
      int eid, this_parent_eid;
      const char *this_name;
      svn_boolean_t is_subbranch;

      SVN_ERR(parse_element_line(&eid,
                                 &is_subbranch, &this_parent_eid, &this_name,
                                 stream, scratch_pool, scratch_pool));

      if (this_name)
        {
          svn_element__payload_t *payload;
          svn_element__content_t *element;

          if (! is_subbranch)
            {
              payload = svn_element__payload_create_ref(txn->rev, bid, eid,
                                                        result_pool);
            }
          else
            {
              payload
                = svn_element__payload_create_subbranch(result_pool);
            }
          element = svn_element__content_create(this_parent_eid,
                                                this_name, payload,
                                                scratch_pool);
          SVN_ERR(branch_state_set_element(branch_state, eid, element,
                                           scratch_pool));
        }
    }

  branch_state->priv->is_flat = TRUE;
  *new_branch = branch_state;
  return SVN_NO_ERROR;
}