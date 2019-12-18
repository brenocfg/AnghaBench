#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  payload; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ svn_element__content_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pmemdup (int /*<<< orphan*/ *,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_element__payload_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_element__content_t *
svn_element__content_dup(const svn_element__content_t *old,
                         apr_pool_t *result_pool)
{
  svn_element__content_t *content
     = apr_pmemdup(result_pool, old, sizeof(*content));

  content->name = apr_pstrdup(result_pool, old->name);
  content->payload = svn_element__payload_dup(old->payload, result_pool);
  return content;
}