#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_2__ {int /*<<< orphan*/  filehandle_pool; int /*<<< orphan*/  scratch_pool; } ;
typedef  TYPE_1__ rep_read_baton_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
rep_read_contents_close(void *baton)
{
  rep_read_baton_t *rb = baton;

  svn_pool_destroy(rb->scratch_pool);
  svn_pool_destroy(rb->filehandle_pool);

  return SVN_NO_ERROR;
}