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
 int* Bq ; 
 int /*<<< orphan*/  Bq_W ; 
 int EXPQ_SIZE ; 
 int now ; 

void store_expired_target (int ip_addr, int port) {
  int i = Bq_W++ & (EXPQ_SIZE - 1);
  Bq[i*3] = ip_addr;
  Bq[i*3+1] = port;
  Bq[i*3+2] = now;
}