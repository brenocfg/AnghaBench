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
typedef  int /*<<< orphan*/  svn_ra_reporter_t ;
typedef  int /*<<< orphan*/  svn_ra_reporter3_t ;
struct compat_report_baton {void* baton; int /*<<< orphan*/  const* reporter; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 struct compat_report_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  compat_reporter ; 

__attribute__((used)) static void compat_wrap_reporter(const svn_ra_reporter_t **reporter,
                                 void **baton,
                                 const svn_ra_reporter3_t *wrapped,
                                 void *wrapped_baton,
                                 apr_pool_t *pool)
{
  struct compat_report_baton *crb = apr_palloc(pool, sizeof(*crb));
  crb->reporter = wrapped;
  crb->baton = wrapped_baton;

  *reporter = &compat_reporter;
  *baton = crb;
}