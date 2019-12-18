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
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ crc32c_process ; 
 int rwm_process (struct raw_message*,int,void*,unsigned int*) ; 

unsigned rwm_crc32c (struct raw_message *raw, int bytes) {
  unsigned crc32c = ~0;

  assert (rwm_process (raw, bytes, (void *)crc32c_process, &crc32c) == bytes);

  return ~crc32c;
}