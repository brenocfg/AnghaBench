#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int i; char* s; int* v; } ;

/* Variables and functions */
 int DL_LOG_SIZE ; 
 int LOG_ID_MX ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* dl_log ; 
 scalar_t__ unlikely (int) ; 

int dl_log_dump_to_buf (int log_id, int verb_min, int verb_max, char *buf, int buf_n, int line_mx)  {
  assert (0 <= log_id && log_id < LOG_ID_MX);

  int i = dl_log[log_id].i, bi = 0;

  do {
    if (--i == -1) {
      i = DL_LOG_SIZE - 1;
    }

    char c = dl_log[log_id].s[i];
    if (unlikely (c == 0)) {
      break;
    }
    if (verb_max >= dl_log[log_id].v[i] && dl_log[log_id].v[i] >= verb_min) {
      if (c == '\n') {
        if (--line_mx < 0) {
          break;
        }
      }
      buf[bi++] = c;
    }
  } while (dl_log[log_id].i != i && bi + 1 < buf_n);
  buf[bi] = 0;
  i = 0;
  int j = bi - 1;
  while (i < j) {
    char t = buf[i];
    buf[i] = buf[j];
    buf[j] = t;
    i++, j--;
  }

  return bi;
}