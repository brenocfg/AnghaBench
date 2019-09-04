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
struct counter {int type; scalar_t__ last_month_unique_visitors; int created_at; struct counter* prev; } ;

/* Variables and functions */
 int COUNTER_TYPE_MONTH ; 
 scalar_t__ Q_raw ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 struct counter* get_counter_f (long long,int /*<<< orphan*/ ) ; 
 int get_month (int) ; 
 int get_monthly_visitors_serialized_raw (char*,long long) ; 
 int get_year (int) ; 
 int load_counter (long long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int get_monthly_visitors_serialized (char *buffer, long long counter_id) {
  if (load_counter (counter_id, 0, 1) == -2) {
    return -2;
  }
  if (Q_raw) {
    return get_monthly_visitors_serialized_raw (buffer, counter_id);
  }
  char *ptr = buffer;
  struct counter *C = get_counter_f (counter_id, 0);
  int r = 0;
  int first = 1;
  while (C) {
    //fprintf (stderr, ".%d %d\n", C->type & COUNTER_TYPE_MONTH, C->last_month_unique_visitors);
    if (first && !(C->type & COUNTER_TYPE_MONTH) && C->last_month_unique_visitors >= 0) {
      int m = get_month (C->created_at);
      int y = get_year (C->created_at);
      m ++;
      r = 1;
      ptr += sprintf (ptr, "%d,%d,%d", C->last_month_unique_visitors, m, y);
      first = 0;
    }
    if (verbosity >= 2) {
      if (C->type & COUNTER_TYPE_MONTH) {
        int m = get_month (C->created_at);
        int y = get_year (C->created_at);
        fprintf (stderr, "%d:%d:%d\n", m, y, C->created_at);
      }
    }
    if ((C->type & COUNTER_TYPE_MONTH) && C->last_month_unique_visitors >= 0) {
      if (first) {
        int m = get_month (C->created_at);
        int y = get_year (C->created_at);
        m ++;
        r = 1;
        ptr += sprintf (ptr, "%d,%d,%d", 0, m, y);
        first = 0;
      }
      if (r) {
        ptr += sprintf (ptr, ",");
      } else {
        r = 1;
      }
      int m = get_month (C->created_at);
      int y = get_year (C->created_at);
      //m--;
      if (!m) {
        m = 12;
        y--;
      }
      ptr += sprintf (ptr, "%d,%d,%d", C->last_month_unique_visitors, m, y);
      //fprintf (stderr, "%d\n", C->created_at);
    }   
    //fprintf (stderr, "%d,%d,%d\n", C->created_at, C->last_month_unique_visitors, C->type & COUNTER_TYPE_MONTH8);
    C = C->prev;
  }
  return ptr - buffer;
}