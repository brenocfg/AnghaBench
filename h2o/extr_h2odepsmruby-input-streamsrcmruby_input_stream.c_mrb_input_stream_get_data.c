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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_int ;
struct TYPE_3__ {char* base; void* free_cb_data; int /*<<< orphan*/  free_cb; int /*<<< orphan*/  pos; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ mrb_input_stream_t ;
typedef  int /*<<< orphan*/  mrb_input_stream_free_callback ;

/* Variables and functions */
 TYPE_1__* DATA_PTR (int /*<<< orphan*/ ) ; 

void
mrb_input_stream_get_data(mrb_state *mrb, mrb_value self, const char **base, mrb_int *len, mrb_int *pos, mrb_input_stream_free_callback *free_cb, void **free_cb_data)
{
  mrb_input_stream_t *stream = DATA_PTR(self);

  if (base != NULL)
    *base = stream->base;
  if (len != NULL)
    *len = stream->len;
  if (pos != NULL)
    *pos = stream->pos;
  if (free_cb != NULL)
    *free_cb = stream->free_cb;
  if (free_cb_data != NULL)
    *free_cb_data = stream->free_cb_data;
}