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
typedef  int mrb_int ;
struct TYPE_3__ {char* base; int len; int pos; int /*<<< orphan*/ * free_cb_data; int /*<<< orphan*/ * free_cb; } ;
typedef  TYPE_1__ mrb_input_stream_t ;
typedef  int /*<<< orphan*/ * mrb_input_stream_free_callback ;

/* Variables and functions */
 int /*<<< orphan*/ * default_free_cb ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void setup_stream(mrb_state *mrb, mrb_input_stream_t *stream, const char *base, mrb_int len, mrb_int pos, mrb_input_stream_free_callback free_cb, void *free_cb_data)
{
  if (free_cb == NULL) {
    if (len > 0) {
      char *dst_base = (char *)mrb_malloc(mrb, sizeof(char)*len);
      memcpy(dst_base, base, len);
      stream->base = dst_base;
      stream->len = len;
    } else {
      stream->base = NULL;
      stream->len = len;
    }
    stream->free_cb = default_free_cb;
    stream->free_cb_data = NULL;
  } else {
    stream->base = base;
    stream->len = len;
    stream->free_cb = free_cb;
    stream->free_cb_data = free_cb_data;
  }

  stream->pos = pos;
}