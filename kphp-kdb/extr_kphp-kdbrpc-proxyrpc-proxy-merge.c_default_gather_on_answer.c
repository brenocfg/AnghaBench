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
struct gather {TYPE_1__* List; } ;
struct TYPE_2__ {int bytes; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int gather_result_memory ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  tl_fetch_raw_data (void*,int) ; 
 int tl_fetch_unread () ; 

void default_gather_on_answer (struct gather *G, int num) {
  int remaining_len = tl_fetch_unread ();
  assert (!(remaining_len & 3));
  G->List[num].bytes = remaining_len;
  G->List[num].data = malloc (remaining_len);
  tl_fetch_raw_data ((void *)G->List[num].data, remaining_len);
  gather_result_memory += remaining_len;
}