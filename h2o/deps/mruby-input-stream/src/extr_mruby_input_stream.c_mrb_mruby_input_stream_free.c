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
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_3__ {int /*<<< orphan*/  free_cb_data; int /*<<< orphan*/  len; int /*<<< orphan*/  base; int /*<<< orphan*/  (* free_cb ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ mrb_input_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mrb_mruby_input_stream_free(mrb_state *mrb, void *ptr)
{
  mrb_input_stream_t *stream = (mrb_input_stream_t *)ptr;
  if (stream->free_cb != NULL)
    stream->free_cb(mrb, stream->base, stream->len, stream->free_cb_data);
  mrb_free(mrb, stream);
}