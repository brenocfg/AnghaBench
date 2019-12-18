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
struct TYPE_4__ {int /*<<< orphan*/ * pool; void* close_handles; void* noecho; int /*<<< orphan*/ * outfd; int /*<<< orphan*/ * infd; } ;
typedef  TYPE_1__ terminal_handle_t ;
typedef  void* svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
terminal_handle_init(terminal_handle_t *terminal,
                     apr_file_t *infd, apr_file_t *outfd,
                     svn_boolean_t noecho, svn_boolean_t close_handles,
                     apr_pool_t *pool)
{
  memset(terminal, 0, sizeof(*terminal));
  terminal->infd = infd;
  terminal->outfd = outfd;
  terminal->noecho = noecho;
  terminal->close_handles = close_handles;
  terminal->pool = pool;
}