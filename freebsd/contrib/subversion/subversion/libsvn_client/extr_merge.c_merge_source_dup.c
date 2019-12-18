#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ancestral; void* loc2; void* loc1; } ;
typedef  TYPE_1__ merge_source_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 void* svn_client__pathrev_dup (void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static merge_source_t *
merge_source_dup(const merge_source_t *source,
                 apr_pool_t *result_pool)
{
  merge_source_t *s = apr_palloc(result_pool, sizeof(*s));

  s->loc1 = svn_client__pathrev_dup(source->loc1, result_pool);
  s->loc2 = svn_client__pathrev_dup(source->loc2, result_pool);
  s->ancestral = source->ancestral;
  return s;
}