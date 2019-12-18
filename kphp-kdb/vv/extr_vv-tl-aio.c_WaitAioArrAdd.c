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
struct aio_connection {int dummy; } ;

/* Variables and functions */
 struct aio_connection** WaitAioArr ; 
 int WaitAioArrPos ; 

int WaitAioArrAdd (struct aio_connection *conn) {
  if (WaitAioArrPos < 99) {
    WaitAioArr[WaitAioArrPos ++] = conn;
    return 1;
  } else {
    return 0;
  }
}