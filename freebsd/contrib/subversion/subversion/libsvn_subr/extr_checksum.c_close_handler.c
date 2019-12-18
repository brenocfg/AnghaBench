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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  digest; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ svn_checksum_t ;
struct TYPE_5__ {int /*<<< orphan*/  inner_stream; TYPE_1__** checksum; scalar_t__ digest; int /*<<< orphan*/  pool; int /*<<< orphan*/  context; } ;
typedef  TYPE_2__ stream_baton_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIGESTSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_final (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
close_handler(void *baton)
{
  stream_baton_t *b = baton;
  svn_checksum_t *local_checksum;

  /* Ensure we can always write to *B->CHECKSUM. */
  if (!b->checksum)
    b->checksum = &local_checksum;

  /* Get the final checksum. */
  SVN_ERR(svn_checksum_final(b->checksum, b->context, b->pool));

  /* Extract digest, if wanted. */
  if (b->digest)
    {
      apr_size_t digest_size = DIGESTSIZE((*b->checksum)->kind);
      memcpy(b->digest, (*b->checksum)->digest, digest_size);
    }

  /* Done here.  Now, close the underlying stream as well. */
  return svn_error_trace(svn_stream_close(b->inner_stream));
}