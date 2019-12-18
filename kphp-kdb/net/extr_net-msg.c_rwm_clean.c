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
struct raw_message {scalar_t__ magic; scalar_t__ total_bytes; scalar_t__ last_offset; scalar_t__ first_offset; scalar_t__ last; scalar_t__ first; } ;

/* Variables and functions */
 scalar_t__ RM_INIT_MAGIC ; 
 scalar_t__ RM_TMP_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 

void rwm_clean (struct raw_message *raw) {
  assert (raw->magic == RM_INIT_MAGIC || raw->magic == RM_TMP_MAGIC);
  raw->first = raw->last = 0;
  raw->first_offset = raw->last_offset = 0;
  raw->total_bytes = 0;
}