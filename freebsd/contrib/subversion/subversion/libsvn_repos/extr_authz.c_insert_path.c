#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_15__ ;

/* Type definitions */
struct TYPE_30__ {int /*<<< orphan*/  rights; } ;
typedef  TYPE_4__ path_access_t ;
struct TYPE_29__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_31__ {TYPE_3__ segment; int /*<<< orphan*/  sub_nodes; TYPE_1__* pattern_sub_nodes; int /*<<< orphan*/  rights; } ;
typedef  TYPE_5__ node_t ;
struct TYPE_32__ {TYPE_5__* node; TYPE_9__* segment; } ;
typedef  TYPE_6__ node_segment_pair_t ;
struct TYPE_33__ {int /*<<< orphan*/  min_rights; int /*<<< orphan*/  max_rights; TYPE_4__ access; } ;
typedef  TYPE_7__ limited_rights_t ;
struct TYPE_34__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_8__ construction_context_t ;
struct TYPE_28__ {int /*<<< orphan*/  data; } ;
struct TYPE_35__ {int kind; TYPE_2__ pattern; } ;
typedef  TYPE_9__ authz_rule_segment_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_27__ {int /*<<< orphan*/  complex; int /*<<< orphan*/  suffixes; int /*<<< orphan*/  prefixes; int /*<<< orphan*/  any_var; int /*<<< orphan*/  any; } ;
struct TYPE_26__ {int /*<<< orphan*/  repeat; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_6__* apr_array_push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
#define  authz_rule_any_recursive 132 
#define  authz_rule_any_segment 131 
#define  authz_rule_fnmatch 130 
 int authz_rule_literal ; 
#define  authz_rule_prefix 129 
#define  authz_rule_suffix 128 
 int /*<<< orphan*/  combine_access (int /*<<< orphan*/ *,TYPE_7__*) ; 
 TYPE_5__* create_node (TYPE_9__*,int /*<<< orphan*/ *) ; 
 TYPE_5__* ensure_node (int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ *) ; 
 TYPE_5__* ensure_node_in_array (int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ *) ; 
 TYPE_15__* ensure_pattern_sub_nodes (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash__make (int /*<<< orphan*/ *) ; 
 TYPE_5__* svn_hash_gets (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
insert_path(construction_context_t *ctx,
            node_t *node,
            path_access_t *path_access,
            int segment_count,
            authz_rule_segment_t *segment,
            apr_pool_t *result_pool,
            apr_pool_t *scratch_pool)
{
  node_t *sub_node;
  node_segment_pair_t *node_segment;

  /* End of path? */
  if (segment_count == 0)
    {
      /* Set access rights.  Note that there might be multiple rules for
       * the same path due to non-repo-specific rules vs. repo-specific
       * ones.  Whichever gets defined last wins.
       */
      limited_rights_t rights;
      rights.access = *path_access;
      rights.max_rights = path_access->rights;
      rights.min_rights = path_access->rights;
      combine_access(&node->rights, &rights);
      return;
    }

  /* Any wildcards?  They will go into a separate sub-structure. */
  if (segment->kind != authz_rule_literal)
    ensure_pattern_sub_nodes(node, result_pool);

  switch (segment->kind)
    {
      /* A full wildcard segment? */
    case authz_rule_any_segment:
      sub_node = ensure_node(&node->pattern_sub_nodes->any,
                             segment, result_pool);
      break;

      /* One or more full wildcard segments? */
    case authz_rule_any_recursive:
      sub_node = ensure_node(&node->pattern_sub_nodes->any_var,
                             segment, result_pool);
      ensure_pattern_sub_nodes(sub_node, result_pool)->repeat = TRUE;
      break;

      /* A single wildcard at the end of the segment? */
    case authz_rule_prefix:
      sub_node = ensure_node_in_array(&node->pattern_sub_nodes->prefixes,
                                      segment, result_pool);
      break;

      /* A single wildcard at the start of segments? */
    case authz_rule_suffix:
      sub_node = ensure_node_in_array(&node->pattern_sub_nodes->suffixes,
                                      segment, result_pool);
      break;

      /* General pattern? */
    case authz_rule_fnmatch:
      sub_node = ensure_node_in_array(&node->pattern_sub_nodes->complex,
                                      segment, result_pool);
      break;

      /* Then it must be a literal. */
    default:
      SVN_ERR_ASSERT_NO_RETURN(segment->kind == authz_rule_literal);

      if (!node->sub_nodes)
        {
          node->sub_nodes = svn_hash__make(result_pool);
          sub_node = NULL;
        }
      else
        {
          sub_node = svn_hash_gets(node->sub_nodes, segment->pattern.data);
        }

      /* Auto-insert a sub-node for the current segment. */
      if (!sub_node)
        {
          sub_node = create_node(segment, result_pool);
          apr_hash_set(node->sub_nodes,
                       sub_node->segment.data,
                       sub_node->segment.len,
                       sub_node);
        }
    }

  /* Update context. */
  node_segment = apr_array_push(ctx->path);
  node_segment->segment = segment;
  node_segment->node = sub_node;

  /* Continue at the sub-node with the next segment. */
  insert_path(ctx, sub_node, path_access, segment_count - 1, segment + 1,
              result_pool, scratch_pool);
}