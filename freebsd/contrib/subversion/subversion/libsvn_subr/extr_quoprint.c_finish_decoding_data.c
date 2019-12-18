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
typedef  int /*<<< orphan*/  svn_error_t ;
struct decode_baton {int /*<<< orphan*/  pool; int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_stream_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
finish_decoding_data(void *baton)
{
  struct decode_baton *db = baton;
  svn_error_t *err;

  /* Pass on the close request and clean up the baton.  */
  err = svn_stream_close(db->output);
  svn_pool_destroy(db->pool);
  return err;
}