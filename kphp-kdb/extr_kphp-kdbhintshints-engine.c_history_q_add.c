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
 size_t MAX_HISTORY ; 
 scalar_t__ dl_strdup (char*) ; 
 int /*<<< orphan*/  dl_strfree (scalar_t__) ; 
 size_t history_l ; 
 scalar_t__* history_q ; 
 size_t history_r ; 
 int* history_t ; 

void history_q_add (char *s, int t) {
  if (s == NULL) {
    return;
  }
  history_t[history_r] = t;
  history_q[history_r++] = dl_strdup (s);
  if (history_r > MAX_HISTORY) {
    history_r = 0;
  }
  if (history_l >= history_r) {
    dl_strfree (history_q[history_l]);
    history_q[history_l++] = 0;
    if (history_l > MAX_HISTORY) {
      history_l = 0;
    }
  }
}