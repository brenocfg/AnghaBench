#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  byte_stream_count; TYPE_2__* last_byte_stream; TYPE_2__* first_byte_stream; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ svn_packed__data_root_t ;
struct TYPE_7__ {struct TYPE_7__* next; int /*<<< orphan*/  packed; } ;
typedef  TYPE_2__ svn_packed__byte_stream_t ;

/* Variables and functions */
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svn_stringbuf_create_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_packed__byte_stream_t *
create_bytes_stream_body(svn_packed__data_root_t *root)
{
  svn_packed__byte_stream_t *stream
    = apr_pcalloc(root->pool, sizeof(*stream));

  stream->packed = svn_stringbuf_create_empty(root->pool);

  if (root->last_byte_stream)
    root->last_byte_stream->next = stream;
  else
    root->first_byte_stream = stream;

  root->last_byte_stream = stream;
  root->byte_stream_count++;

  return stream;
}