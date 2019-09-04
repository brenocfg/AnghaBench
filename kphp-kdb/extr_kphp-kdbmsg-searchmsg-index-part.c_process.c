#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int user_id; int /*<<< orphan*/  prev; } ;
typedef  TYPE_1__ entry_t ;

/* Variables and functions */
 int /*<<< orphan*/ * LastMsg ; 
 int get_hash (int) ; 
 int mod ; 
 int /*<<< orphan*/  msgs_analyzed ; 
 int /*<<< orphan*/  msgs_read ; 
 int rem ; 
 int /*<<< orphan*/  store_entry (TYPE_1__*) ; 

void process (entry_t *E) {
  int mid = E->user_id;
  int h = get_hash (mid);
  msgs_read++;
  if (mid % mod == rem) {
    E->prev = LastMsg [h];
    LastMsg[h] = store_entry (E);
    msgs_analyzed++;
  }
//  printf ("%ld %ld %ld %ld %s\n", E->user_id, E->peer_id, E->message_id, E->date, E->text);
}