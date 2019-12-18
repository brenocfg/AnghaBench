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
typedef  int /*<<< orphan*/  svn_packed__int_stream_t ;
typedef  int /*<<< orphan*/  apr_uint64_t ;
typedef  scalar_t__ apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_packed__add_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
svn_packed__add_int(svn_packed__int_stream_t *stream,
                    apr_int64_t value)
{
  svn_packed__add_uint(stream, (apr_uint64_t)value);
}