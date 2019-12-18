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
typedef  int /*<<< orphan*/  svn_ra_serf__request_body_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__request_body_delegate_t ;

/* Variables and functions */
 int /*<<< orphan*/  request_body_delegate ; 

void
svn_ra_serf__request_body_get_delegate(svn_ra_serf__request_body_delegate_t *del,
                                       void **baton,
                                       svn_ra_serf__request_body_t *body)
{
  *del = request_body_delegate;
  *baton = body;
}