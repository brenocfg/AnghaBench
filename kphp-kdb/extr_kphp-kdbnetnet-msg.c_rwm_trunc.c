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
struct raw_message {int total_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  rwm_fetch_data_back (struct raw_message*,int /*<<< orphan*/ ,int) ; 

int rwm_trunc (struct raw_message *raw, int len) {
  if (len >= raw->total_bytes) { 
    return raw->total_bytes;
  }
  rwm_fetch_data_back (raw, 0, raw->total_bytes - len);
  return len;
}