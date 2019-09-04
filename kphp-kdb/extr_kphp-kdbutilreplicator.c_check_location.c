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
struct remote_binlog {char* binlog_tag; struct location_list_entry* first; } ;
struct location_list_entry {int flags; char* location; struct location_list_entry* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct remote_binlog*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

int check_location (struct remote_binlog *B) {
  assert (B);

  int l_cnt = 0, m_cnt = 0;
  struct location_list_entry *Q;
  for (Q = B->first; Q; Q = Q->next) {
    if (Q->flags & 2) {
      l_cnt++;
    }
    if (Q->flags & 1) {
      m_cnt++;
    }
  }

  if (l_cnt > 1) {
    fprintf (stderr, "error: binlog %s has %d local locations:", B->binlog_tag, l_cnt);
    for (Q = B->first; Q; Q = Q->next) {
      if (Q->flags & 2) {
        fprintf (stderr, " %s", Q->location);
      }
    }
    fprintf (stderr, "\n");
    return 1;
  }

  if (!m_cnt) {
    fprintf (stderr, "error: binlog %s has no master location\n", B->binlog_tag);
    return 1;
  }

  if (m_cnt > 1) {
    fprintf (stderr, "error: binlog %s has %d master locations:", B->binlog_tag, m_cnt);
    for (Q = B->first; Q; Q = Q->next) {
      if (Q->flags & 1) {
        fprintf (stderr, " %s", Q->location);
      }
    }
    fprintf (stderr, "\n");
    return 1;
  }

  return 0;
}