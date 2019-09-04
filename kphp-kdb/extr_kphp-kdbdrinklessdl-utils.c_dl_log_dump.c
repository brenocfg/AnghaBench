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
struct TYPE_2__ {int i; int* v; scalar_t__* s; scalar_t__ f; } ;

/* Variables and functions */
 int DL_LOG_SIZE ; 
 int LOG_ID_MX ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* dl_log ; 
 int /*<<< orphan*/  putc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void dl_log_dump (int log_id, int verb) {
  assert (0 <= log_id && log_id < LOG_ID_MX);
  int i = (dl_log[log_id].f ? dl_log[log_id].i : 0);

  do {
    if (dl_log[log_id].s[i] && verb >= dl_log[log_id].v[i]) {
      putc (dl_log[log_id].s[i], stderr);
    }
    if (++i == DL_LOG_SIZE) {
      i = 0;
    }
  } while (dl_log[log_id].i != i);
}