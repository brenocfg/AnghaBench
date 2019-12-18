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
 int _secure_send_on_net_fail (void**,void**,int) ; 

int secure_send_on_net_fail_binlog (void **IP, void **Data) {
  return _secure_send_on_net_fail (IP, Data, 1);
}