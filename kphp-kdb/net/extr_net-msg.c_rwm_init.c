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
 int rwm_create (struct raw_message*,int /*<<< orphan*/ ,int) ; 

int rwm_init (struct raw_message *raw, int alloc_bytes) {
  return rwm_create (raw, 0, alloc_bytes);
}