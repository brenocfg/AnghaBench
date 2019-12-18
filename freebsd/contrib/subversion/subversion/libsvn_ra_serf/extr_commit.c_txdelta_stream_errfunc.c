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
struct TYPE_2__ {int /*<<< orphan*/  err; } ;
typedef  TYPE_1__ open_txdelta_baton_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_error_compose_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_dup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
txdelta_stream_errfunc(void *baton, svn_error_t *err)
{
  open_txdelta_baton_t *b = baton;

  /* Remember extended error info from the stream bucket.  Note that
   * theoretically this errfunc could be called multiple times -- say,
   * if the request gets restarted after an error.  Compose the errors
   * so we don't leak one of them if this happens. */
  b->err = svn_error_compose_create(b->err, svn_error_dup(err));
}