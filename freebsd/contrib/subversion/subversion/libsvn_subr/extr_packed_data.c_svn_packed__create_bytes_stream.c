#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  int_stream_count; } ;
typedef  TYPE_1__ svn_packed__data_root_t ;
struct TYPE_9__ {int /*<<< orphan*/  lengths_stream; int /*<<< orphan*/  lengths_stream_index; } ;
typedef  TYPE_2__ svn_packed__byte_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_2__* create_bytes_stream_body (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_packed__create_int_stream (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_packed__byte_stream_t *
svn_packed__create_bytes_stream(svn_packed__data_root_t *root)
{
  svn_packed__byte_stream_t *stream
    = create_bytes_stream_body(root);

  stream->lengths_stream_index = root->int_stream_count;
  stream->lengths_stream = svn_packed__create_int_stream(root, FALSE, FALSE);

  return stream;
}