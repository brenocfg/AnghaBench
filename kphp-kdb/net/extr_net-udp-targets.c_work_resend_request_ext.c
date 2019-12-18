#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int total_bytes; } ;
struct udp_msg {int /*<<< orphan*/  S; TYPE_1__ raw; } ;

/* Variables and functions */
 int TL_UDP_RESEND_REQUEST_EXT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  resend_range (int /*<<< orphan*/ ,int,int,int) ; 
 int rwm_fetch_data (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

int work_resend_request_ext (struct udp_msg *msg) {
  vkprintf (2, "work_resend_request: len = %d\n", msg->raw.total_bytes);
  if (msg->raw.total_bytes > 102 * 4) { return 0; }
  int len =  msg->raw.total_bytes;
  static int P[102];
  assert (rwm_fetch_data (&msg->raw, P, len) == len);  
  if ((P[1] + 1) * 8 != len) { return 0; }
  assert (P[0] == TL_UDP_RESEND_REQUEST_EXT);
  int i;
  //vkprintf (0, "resend request: num = %d\n", P[1]);
  for (i = 0; i < P[1]; i++) {
    if (P[2 + 2 * i] <= P[2 + 2 * i + 1]) {
      resend_range (msg->S, P[2 + 2 * i], P[2 + 2 * i + 1], 1);
    }
  }
  return 0;
}