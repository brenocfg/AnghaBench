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
typedef  int /*<<< orphan*/  svn_config_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_3__ {void* anon_access; void* auth_access; } ;
typedef  TYPE_1__ repository_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_CONFIG_OPTION_ANON_ACCESS ; 
 int /*<<< orphan*/  SVN_CONFIG_OPTION_AUTH_ACCESS ; 
 void* get_access (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_access(repository_t *repository,
           svn_config_t *cfg,
           svn_boolean_t read_only)
{
  repository->auth_access = get_access(cfg, SVN_CONFIG_OPTION_AUTH_ACCESS,
                                       "write", read_only);
  repository->anon_access = get_access(cfg, SVN_CONFIG_OPTION_ANON_ACCESS,
                                       "read", read_only);
}