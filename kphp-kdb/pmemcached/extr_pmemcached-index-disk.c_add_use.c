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
 int MAX_METAFILES ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t* next_use ; 
 int* prev_use ; 

void add_use (int metafile_number) {
  assert (0 <= metafile_number && metafile_number < MAX_METAFILES);
  prev_use[metafile_number] = MAX_METAFILES;
  next_use[metafile_number] = next_use[MAX_METAFILES];
  next_use[MAX_METAFILES] = metafile_number;
  prev_use[next_use[metafile_number]] = metafile_number;
}