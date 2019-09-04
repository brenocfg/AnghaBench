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
 int STAT_EV ; 
 int /*<<< orphan*/  assert (int) ; 
 int idn ; 
 int* q_events ; 
 int qel ; 
 int qen ; 
 size_t qer ; 
 int /*<<< orphan*/  upd_stat_ (int,int) ; 

void upd_stat (int id) {
  assert (-idn <= id && id <= idn && id != 0);

  if (qen > STAT_EV - 5) {
    upd_stat_ (q_events[qel++], -1);
    qen--;
    if (qel == STAT_EV) {
      qel = 0;
    }
  }

  q_events[qer] = id;
  upd_stat_ (q_events[qer++], +1);
  qen++;
  if (qer == STAT_EV) {
    qer = 0;
  }
}