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
typedef  int /*<<< orphan*/  svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct encoder_baton {int version; int compression_level; int /*<<< orphan*/  scratch_pool; int /*<<< orphan*/  header_done; int /*<<< orphan*/ * output; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 struct encoder_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  window_handler ; 

void
svn_txdelta_to_svndiff3(svn_txdelta_window_handler_t *handler,
                        void **handler_baton,
                        svn_stream_t *output,
                        int svndiff_version,
                        int compression_level,
                        apr_pool_t *pool)
{
  struct encoder_baton *eb;

  eb = apr_palloc(pool, sizeof(*eb));
  eb->output = output;
  eb->header_done = FALSE;
  eb->scratch_pool = svn_pool_create(pool);
  eb->version = svndiff_version;
  eb->compression_level = compression_level;

  *handler = window_handler;
  *handler_baton = eb;
}