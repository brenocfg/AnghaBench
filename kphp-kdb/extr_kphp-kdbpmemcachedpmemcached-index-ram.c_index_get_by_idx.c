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
struct index_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * index_binary_data ; 
 size_t* index_offset ; 

inline struct index_entry* index_get_by_idx ( int idx ) {
  return (struct index_entry *)&index_binary_data[index_offset[idx]];
}