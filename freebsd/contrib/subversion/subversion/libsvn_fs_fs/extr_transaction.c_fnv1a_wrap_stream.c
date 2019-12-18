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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_checksum_ctx_t ;
struct TYPE_4__ {int /*<<< orphan*/ * context; int /*<<< orphan*/ * inner_stream; } ;
typedef  TYPE_1__ fnv1a_stream_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fnv1a_write_handler ; 
 int /*<<< orphan*/ * svn_checksum_ctx_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_fnv1a_32x4 ; 
 int /*<<< orphan*/ * svn_stream_create (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_stream_t *
fnv1a_wrap_stream(svn_checksum_ctx_t **context,
                  svn_stream_t *inner_stream,
                  apr_pool_t *pool)
{
  svn_stream_t *outer_stream;

  fnv1a_stream_baton_t *baton = apr_pcalloc(pool, sizeof(*baton));
  baton->inner_stream = inner_stream;
  baton->context = svn_checksum_ctx_create(svn_checksum_fnv1a_32x4, pool);
  *context = baton->context;

  outer_stream = svn_stream_create(baton, pool);
  svn_stream_set_write(outer_stream, fnv1a_write_handler);

  return outer_stream;
}