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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
translate_write(svn_stream_t *stream,
                const void *buf,
                apr_size_t len)
{
  SVN_ERR(svn_stream_write(stream, buf, &len));
  /* (No need to check LEN, as a short write always produces an error.) */
  return SVN_NO_ERROR;
}