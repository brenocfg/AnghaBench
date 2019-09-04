#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_int ;
struct TYPE_4__ {int /*<<< orphan*/  free_cb_data; int /*<<< orphan*/  len; int /*<<< orphan*/  base; int /*<<< orphan*/  (* free_cb ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ mrb_input_stream_t ;
typedef  int /*<<< orphan*/  mrb_input_stream_free_callback ;

/* Variables and functions */
 TYPE_1__* DATA_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_stream (int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mrb_input_stream_set_data(mrb_state *mrb, mrb_value self, const char *base, mrb_int len, mrb_int pos, mrb_input_stream_free_callback free_cb, void *free_cb_data)
{
  mrb_input_stream_t *stream = DATA_PTR(self);

  if (stream->free_cb != NULL)
    stream->free_cb(mrb, stream->base, stream->len, stream->free_cb_data);
  setup_stream(mrb, stream, base, len, pos, free_cb, free_cb_data);
}