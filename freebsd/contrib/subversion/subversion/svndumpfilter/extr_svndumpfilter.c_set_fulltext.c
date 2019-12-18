#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct node_baton_t {TYPE_2__* rb; int /*<<< orphan*/  node_pool; int /*<<< orphan*/  tcl; void* has_text; int /*<<< orphan*/ * props; scalar_t__ has_props; int /*<<< orphan*/  headers; void* writing_begun; int /*<<< orphan*/  do_skip; } ;
struct TYPE_4__ {TYPE_1__* pb; } ;
struct TYPE_3__ {int /*<<< orphan*/ * out_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/  svn_repos__dump_node_record (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stringbuf_appendcstr (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static svn_error_t *
set_fulltext(svn_stream_t **stream, void *node_baton)
{
  struct node_baton_t *nb = node_baton;

  if (!nb->do_skip)
    {
      nb->has_text = TRUE;
      if (! nb->writing_begun)
        {
          nb->writing_begun = TRUE;
          if (nb->has_props)
            {
              svn_stringbuf_appendcstr(nb->props, "PROPS-END\n");
            }
          SVN_ERR(svn_repos__dump_node_record(nb->rb->pb->out_stream,
                                              nb->headers,
                                              nb->has_props ? nb->props : NULL,
                                              nb->has_text,
                                              nb->tcl,
                                              TRUE /*content_length_always*/,
                                              nb->node_pool));
        }
      *stream = nb->rb->pb->out_stream;
    }

  return SVN_NO_ERROR;
}