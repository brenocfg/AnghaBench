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
typedef  size_t mrb_int ;
struct TYPE_3__ {char* base; size_t len; size_t pos; } ;
typedef  TYPE_1__ mrb_input_stream_t ;

/* Variables and functions */

__attribute__((used)) static mrb_int
seek_char(mrb_input_stream_t *stream, char chr){
  const char *base = stream->base;
  size_t len = stream->len;
  mrb_int pos = stream->pos;
  const char *end = base + len;
  const char *start = base + pos;
  const char *s = start;

  if (pos >= len) {
    return -1;
  }

  while (s < end) {
    if (*s == chr) {
      break;
    }
    s++;
  }
  return (s - start);
}