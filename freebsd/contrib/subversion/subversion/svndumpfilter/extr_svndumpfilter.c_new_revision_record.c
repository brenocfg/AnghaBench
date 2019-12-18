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
typedef  int /*<<< orphan*/  svn_error_t ;
struct revision_baton_t {int /*<<< orphan*/  rev_orig; int /*<<< orphan*/  rev_actual; TYPE_1__* pb; int /*<<< orphan*/  original_headers; int /*<<< orphan*/  props; void* writing_begun; void* had_dropped_nodes; void* has_nodes; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_2__ {int rev_drop_count; scalar_t__ do_renumber_revs; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_REVISION_NUMBER ; 
 int /*<<< orphan*/  SVN_STR_TO_REV (char const*) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 void* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  headers_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
new_revision_record(void **revision_baton,
                    apr_hash_t *headers,
                    void *parse_baton,
                    apr_pool_t *pool)
{
  struct revision_baton_t *rb;
  const char *rev_orig;

  *revision_baton = apr_palloc(pool, sizeof(struct revision_baton_t));
  rb = *revision_baton;
  rb->pb = parse_baton;
  rb->has_nodes = FALSE;
  rb->had_dropped_nodes = FALSE;
  rb->writing_begun = FALSE;
  rb->props = apr_hash_make(pool);
  rb->original_headers = headers_dup(headers, pool);

  rev_orig = svn_hash_gets(headers, SVN_REPOS_DUMPFILE_REVISION_NUMBER);
  rb->rev_orig = SVN_STR_TO_REV(rev_orig);

  if (rb->pb->do_renumber_revs)
    rb->rev_actual = rb->rev_orig - rb->pb->rev_drop_count;
  else
    rb->rev_actual = rb->rev_orig;

  return SVN_NO_ERROR;
}