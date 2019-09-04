#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kprintf_multiprocessing_mode_enable () ; 
 char* logname ; 
 void* logname_pattern ; 
 void* strdup (char*) ; 

void init_logname (char *src) {
  char *t = src;
  while (*t && *t != '%') {
    t++;
  }
  int has_percent = *t == '%';
  if (!has_percent) {
    logname = src;
    kprintf_multiprocessing_mode_enable();
    return;
  }

  char buf1[100];
  char buf2[100];
  int buf_len = 100;

  char *patt = buf1;
  char *plane = buf2;

  int was_percent = 0;
  while (*src) {
    assert (patt < buf1 + buf_len - 3);
    if (*src == '%') {
      if (!was_percent) {
        *patt++ = '%';
        *patt++ = 'd';
        was_percent = 1;
      }
    } else {
      *patt++ = *src;
      *plane++ = *src;
    }
    src++;
  }
  *patt = 0;
  patt = buf1;
  *plane = 0;
  plane = buf2;

  logname = strdup (plane);
  logname_pattern = strdup (patt);
}