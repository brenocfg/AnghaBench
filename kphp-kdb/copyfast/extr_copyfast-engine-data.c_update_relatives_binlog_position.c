#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {long long id; } ;
struct relative {int type; long long binlog_position; struct relative* next; int /*<<< orphan*/  timestamp; TYPE_2__ node; } ;
struct TYPE_8__ {struct relative* next; } ;
struct TYPE_5__ {long long last_known_binlog_position; int /*<<< orphan*/  last_known_binlog_position_time; } ;
struct TYPE_7__ {TYPE_1__ structured; } ;

/* Variables and functions */
 long long BINLOG_POSITION ; 
 TYPE_4__ RELATIVES ; 
 TYPE_3__* STATS ; 
 int /*<<< orphan*/  get_double_time_since_epoch () ; 
 int /*<<< orphan*/  precise_now ; 

int update_relatives_binlog_position (long long id, long long binlog_position) {
  int i = 0;
  struct relative *cur = RELATIVES.next;
  while (cur->type != -1) {
    if (cur->node.id == id) {
      if (cur->binlog_position <= BINLOG_POSITION && binlog_position > BINLOG_POSITION) {
        cur->timestamp = precise_now; 
      }
      cur->binlog_position = binlog_position;
      i++;
    }
    cur = cur->next;
  }
  if (binlog_position > STATS->structured.last_known_binlog_position) {
    STATS->structured.last_known_binlog_position = binlog_position;
    STATS->structured.last_known_binlog_position_time = get_double_time_since_epoch();
  }
  return i;
}