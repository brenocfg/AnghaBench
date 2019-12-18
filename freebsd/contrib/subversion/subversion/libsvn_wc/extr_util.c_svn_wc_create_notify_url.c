#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* url; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  svn_wc_notify_action_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* svn_wc_create_notify (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_wc_notify_t *
svn_wc_create_notify_url(const char *url,
                         svn_wc_notify_action_t action,
                         apr_pool_t *pool)
{
  svn_wc_notify_t *ret = svn_wc_create_notify(".", action, pool);
  ret->url = url;

  return ret;
}