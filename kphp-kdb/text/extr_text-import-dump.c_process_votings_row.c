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
struct TYPE_2__ {int owner_id; int topic_id; int voting_id; } ;

/* Variables and functions */
 int* I ; 
 size_t MAX_VOTINGS ; 
 TYPE_1__* VD ; 
 size_t VN ; 
 int /*<<< orphan*/  adj_rec ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t vt_id ; 
 size_t vt_owner_id ; 
 size_t vt_place_id ; 
 size_t vt_place_type ; 

void process_votings_row (void) {
  int owner_id = I[vt_owner_id], topic_id = I[vt_place_id], voting_id = I[vt_id];
  if (I[vt_place_type] != 2 || owner_id >= 0 || topic_id <= 0 || voting_id <= 0) {
    return;
  }
  assert (VN < MAX_VOTINGS);
  VD[VN].owner_id = owner_id;
  VD[VN].topic_id = topic_id;
  VD[VN].voting_id = voting_id;
  VN++;

  adj_rec++;
}