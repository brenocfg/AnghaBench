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
typedef  int /*<<< orphan*/  svn_filesize_t ;
struct length_verify_baton_t {int /*<<< orphan*/  remaining; int /*<<< orphan*/ * inner; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 struct length_verify_baton_t* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  close_handler_length_verify ; 
 int /*<<< orphan*/  read_handler_length_verify ; 
 int /*<<< orphan*/ * svn_stream_create (struct length_verify_baton_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_stream_t *
get_verify_length_stream(svn_stream_t *inner,
                         svn_filesize_t expected_size,
                         apr_pool_t *result_pool)
{
  struct length_verify_baton_t *lvb = apr_palloc(result_pool, sizeof(*lvb));
  svn_stream_t *len_stream = svn_stream_create(lvb, result_pool);

  lvb->inner = inner;
  lvb->remaining = expected_size;

  svn_stream_set_read2(len_stream, NULL /* only full read support */,
                       read_handler_length_verify);
  svn_stream_set_close(len_stream, close_handler_length_verify);

  return len_stream;
}