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
struct raw_message {int dummy; } ;

/* Variables and functions */
 int rwm_split (struct raw_message*,struct raw_message*,int) ; 

int rwm_split_head (struct raw_message *head, struct raw_message *raw, int bytes) {
  *head = *raw;
  return rwm_split (head, raw, bytes);
}