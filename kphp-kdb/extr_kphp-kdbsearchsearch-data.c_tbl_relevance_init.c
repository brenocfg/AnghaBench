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
 scalar_t__ Q_Relevance_Power ; 
 int /*<<< orphan*/  Q_relevance ; 
 int RELEVANCE_TABLE_SIZE ; 
 int fabs (scalar_t__) ; 
 scalar_t__ old_Q_Relevance_Power ; 
 double* tbl_relevance ; 

__attribute__((used)) static void tbl_relevance_init (void) {
  int i;
  if (!Q_relevance) { return; }
  if (fabs (old_Q_Relevance_Power - Q_Relevance_Power) < 1e-9) {
    Q_Relevance_Power = old_Q_Relevance_Power;
    return;
  }
  old_Q_Relevance_Power = Q_Relevance_Power;
  for (i = 0; i < RELEVANCE_TABLE_SIZE; i++) {
    tbl_relevance[i] = -1.0;
  }
}