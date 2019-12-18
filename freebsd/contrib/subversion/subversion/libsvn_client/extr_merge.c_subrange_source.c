#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_8__ {scalar_t__ rev; int /*<<< orphan*/  url; } ;
typedef  TYPE_1__ svn_client__pathrev_t ;
typedef  int svn_boolean_t ;
struct TYPE_9__ {int ancestral; TYPE_1__* loc2; TYPE_1__* loc1; } ;
typedef  TYPE_2__ merge_source_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int) ; 
 TYPE_2__* merge_source_create (TYPE_1__*,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static merge_source_t *
subrange_source(const merge_source_t *source,
                svn_revnum_t start_rev,
                svn_revnum_t end_rev,
                apr_pool_t *pool)
{
  svn_boolean_t is_rollback = (source->loc1->rev > source->loc2->rev);
  svn_boolean_t same_urls = (strcmp(source->loc1->url, source->loc2->url) == 0);
  svn_client__pathrev_t loc1 = *source->loc1;
  svn_client__pathrev_t loc2 = *source->loc2;

  /* For this function we require that the input source is 'ancestral'. */
  SVN_ERR_ASSERT_NO_RETURN(source->ancestral);
  SVN_ERR_ASSERT_NO_RETURN(start_rev != end_rev);

  loc1.rev = start_rev;
  loc2.rev = end_rev;
  if (! same_urls)
    {
      if (is_rollback && (end_rev != source->loc2->rev))
        {
          loc2.url = source->loc1->url;
        }
      if ((! is_rollback) && (start_rev != source->loc1->rev))
        {
          loc1.url = source->loc2->url;
        }
    }
  return merge_source_create(&loc1, &loc2, source->ancestral, pool);
}