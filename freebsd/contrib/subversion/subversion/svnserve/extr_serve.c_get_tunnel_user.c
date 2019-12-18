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
struct TYPE_3__ {char const* tunnel_user; int /*<<< orphan*/  tunnel; } ;
typedef  TYPE_1__ serve_params_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* svn_user_get_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *get_tunnel_user(serve_params_t *params, apr_pool_t *pool)
{
  /* Only offer EXTERNAL for connections tunneled over a login agent. */
  if (!params->tunnel)
    return NULL;

  /* If a tunnel user was provided on the command line, use that. */
  if (params->tunnel_user)
    return params->tunnel_user;

  return svn_user_get_name(pool);
}