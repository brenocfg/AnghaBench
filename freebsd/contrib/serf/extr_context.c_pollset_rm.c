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
struct TYPE_5__ {int /*<<< orphan*/  pollset; } ;
typedef  TYPE_1__ serf_pollset_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_6__ {void* client_data; } ;
typedef  TYPE_2__ apr_pollfd_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_pollset_remove (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static apr_status_t pollset_rm(void *user_baton,
                               apr_pollfd_t *pfd,
                               void *serf_baton)
{
    serf_pollset_t *s = (serf_pollset_t*)user_baton;
    pfd->client_data = serf_baton;
    return apr_pollset_remove(s->pollset, pfd);
}