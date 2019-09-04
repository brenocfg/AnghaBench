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
 int* GT ; 
 int Gc ; 
 int* I ; 
 int MAX_GROUPS ; 
 int /*<<< orphan*/  adj_rec ; 
 size_t gs_id ; 
 size_t gs_subtype ; 

void process_groupshort_row (void) {
  int x = I[gs_id], y = I[gs_subtype];
  if (x <= 0 || x >= MAX_GROUPS || y <= 0 || y >= 128) {
    return;
  }
  GT[x] = y;
  if (x >= Gc) { Gc = x+1; }
  adj_rec++;
}