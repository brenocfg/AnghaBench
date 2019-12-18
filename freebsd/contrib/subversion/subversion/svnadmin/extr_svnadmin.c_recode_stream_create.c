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
typedef  int /*<<< orphan*/  svn_stream_t ;
struct recode_write_baton {int /*<<< orphan*/ * out; int /*<<< orphan*/  pool; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct recode_write_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  recode_write ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_create (struct recode_write_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_stream_t *
recode_stream_create(FILE *std_stream, apr_pool_t *pool)
{
  struct recode_write_baton *std_stream_rwb =
    apr_palloc(pool, sizeof(struct recode_write_baton));

  svn_stream_t *rw_stream = svn_stream_create(std_stream_rwb, pool);
  std_stream_rwb->pool = svn_pool_create(pool);
  std_stream_rwb->out = std_stream;
  svn_stream_set_write(rw_stream, recode_write);
  return rw_stream;
}