#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  log_fd; } ;
struct TYPE_5__ {TYPE_1__ log_context; } ;
typedef  TYPE_2__ kadm5_server_context ;
typedef  int /*<<< orphan*/  kadm5_ret_t ;

/* Variables and functions */
 int /*<<< orphan*/  kadm5_log_get_version_fd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kadm5_ret_t
kadm5_log_get_version (kadm5_server_context *context, uint32_t *ver)
{
    return kadm5_log_get_version_fd (context->log_context.log_fd, ver);
}