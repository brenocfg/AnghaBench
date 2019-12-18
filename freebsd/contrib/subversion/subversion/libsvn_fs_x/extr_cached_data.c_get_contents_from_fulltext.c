#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_5__ {scalar_t__ fulltext_delivered; int /*<<< orphan*/  scratch_pool; int /*<<< orphan*/  fulltext_cache_key; int /*<<< orphan*/  fulltext_cache; } ;
typedef  TYPE_1__ rep_read_baton_t ;
struct TYPE_6__ {char* buffer; scalar_t__ read; scalar_t__ len; scalar_t__ start; } ;
typedef  TYPE_2__ fulltext_baton_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_fulltext_partial ; 
 int /*<<< orphan*/  svn_cache__get_partial (void**,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
get_contents_from_fulltext(svn_boolean_t *cached,
                           rep_read_baton_t *baton,
                           char *buffer,
                           apr_size_t *len)
{
  void *dummy;
  fulltext_baton_t fulltext_baton;

  SVN_ERR_ASSERT((apr_size_t)baton->fulltext_delivered
                 == baton->fulltext_delivered);
  fulltext_baton.buffer = buffer;
  fulltext_baton.start = (apr_size_t)baton->fulltext_delivered;
  fulltext_baton.len = *len;
  fulltext_baton.read = 0;

  SVN_ERR(svn_cache__get_partial(&dummy, cached, baton->fulltext_cache,
                                 &baton->fulltext_cache_key,
                                 get_fulltext_partial, &fulltext_baton,
                                 baton->scratch_pool));

  if (*cached)
    {
      baton->fulltext_delivered += fulltext_baton.read;
      *len = fulltext_baton.read;
    }

  return SVN_NO_ERROR;
}