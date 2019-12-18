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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int context_size; int next_slot; size_t* len; scalar_t__* data; } ;
typedef  TYPE_1__ context_saver_t ;
typedef  size_t apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ *,scalar_t__,size_t*) ; 

__attribute__((used)) static svn_error_t *
flush_context_saver(context_saver_t *cs,
                    svn_stream_t *output_stream)
{
  int i;
  for (i = 0; i < cs->context_size; i++)
    {
      apr_size_t slot = (i + cs->next_slot) % cs->context_size;
      if (cs->data[slot])
        {
          apr_size_t len = cs->len[slot];
          SVN_ERR(svn_stream_write(output_stream, cs->data[slot], &len));
        }
    }
  return SVN_NO_ERROR;
}