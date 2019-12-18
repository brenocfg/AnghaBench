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
struct TYPE_3__ {unsigned char const* (* md5_digest ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  baton; } ;
typedef  TYPE_1__ svn_txdelta_stream_t ;

/* Variables and functions */
 unsigned char const* stub1 (int /*<<< orphan*/ ) ; 

const unsigned char *
svn_txdelta_md5_digest(svn_txdelta_stream_t *stream)
{
  return stream->md5_digest(stream->baton);
}