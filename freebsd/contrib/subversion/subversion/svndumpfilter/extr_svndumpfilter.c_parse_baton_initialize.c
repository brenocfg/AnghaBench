#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct svndumpfilter_opt_state {int /*<<< orphan*/  skip_missing_merge_sources; int /*<<< orphan*/  prefixes; int /*<<< orphan*/  glob; int /*<<< orphan*/  quiet; int /*<<< orphan*/  preserve_revprops; scalar_t__ drop_all_empty_revs; scalar_t__ drop_empty_revs; scalar_t__ renumber_revs; } ;
struct parse_baton_t {int do_renumber_revs; int /*<<< orphan*/  allow_deltas; void* oldest_original_rev; void* last_live_revision; void* renumber_history; void* dropped_nodes; scalar_t__ rev_drop_count; int /*<<< orphan*/  skip_missing_merge_sources; int /*<<< orphan*/  prefixes; int /*<<< orphan*/  glob; int /*<<< orphan*/  quiet; int /*<<< orphan*/  preserve_revprops; scalar_t__ drop_all_empty_revs; scalar_t__ drop_empty_revs; int /*<<< orphan*/  do_exclude; int /*<<< orphan*/  out_stream; int /*<<< orphan*/  in_stream; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 void* SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 void* apr_hash_make (int /*<<< orphan*/ *) ; 
 struct parse_baton_t* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_stream_for_stdin2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_for_stdout (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
parse_baton_initialize(struct parse_baton_t **pb,
                       struct svndumpfilter_opt_state *opt_state,
                       svn_boolean_t do_exclude,
                       apr_pool_t *pool)
{
  struct parse_baton_t *baton = apr_palloc(pool, sizeof(*baton));

  /* Read the stream from STDIN.  Users can redirect a file. */
  SVN_ERR(svn_stream_for_stdin2(&baton->in_stream, TRUE, pool));

  /* Have the parser dump results to STDOUT. Users can redirect a file. */
  SVN_ERR(svn_stream_for_stdout(&baton->out_stream, pool));

  baton->do_exclude = do_exclude;

  /* Ignore --renumber-revs if there can't possibly be
     anything to renumber. */
  baton->do_renumber_revs =
    (opt_state->renumber_revs && (opt_state->drop_empty_revs
                                  || opt_state->drop_all_empty_revs));

  baton->drop_empty_revs = opt_state->drop_empty_revs;
  baton->drop_all_empty_revs = opt_state->drop_all_empty_revs;
  baton->preserve_revprops = opt_state->preserve_revprops;
  baton->quiet = opt_state->quiet;
  baton->glob = opt_state->glob;
  baton->prefixes = opt_state->prefixes;
  baton->skip_missing_merge_sources = opt_state->skip_missing_merge_sources;
  baton->rev_drop_count = 0; /* used to shift revnums while filtering */
  baton->dropped_nodes = apr_hash_make(pool);
  baton->renumber_history = apr_hash_make(pool);
  baton->last_live_revision = SVN_INVALID_REVNUM;
  baton->oldest_original_rev = SVN_INVALID_REVNUM;
  baton->allow_deltas = FALSE;

  *pb = baton;
  return SVN_NO_ERROR;
}