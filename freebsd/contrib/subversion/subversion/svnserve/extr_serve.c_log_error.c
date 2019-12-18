#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  client_info; int /*<<< orphan*/  repository; int /*<<< orphan*/  logger; } ;
typedef  TYPE_1__ server_baton_t ;

/* Variables and functions */
 int /*<<< orphan*/  logger__log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
log_error(svn_error_t *err, server_baton_t *server)
{
  logger__log_error(server->logger, err, server->repository,
                    server->client_info);
}