#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lengths_stream; } ;
typedef  TYPE_1__ svn_packed__byte_stream_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_packed__int_count (int /*<<< orphan*/ ) ; 

apr_size_t
svn_packed__byte_block_count(svn_packed__byte_stream_t *stream)
{
  return svn_packed__int_count(stream->lengths_stream);
}