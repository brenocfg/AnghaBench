#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* repository; TYPE_1__* client_info; } ;
typedef  TYPE_3__ server_baton_t ;
typedef  enum access_type { ____Placeholder_access_type } access_type ;
struct TYPE_6__ {int auth_access; int anon_access; } ;
struct TYPE_5__ {scalar_t__ user; } ;

/* Variables and functions */

__attribute__((used)) static enum access_type
current_access(server_baton_t *b)
{
  return b->client_info->user ? b->repository->auth_access
                              : b->repository->anon_access;
}