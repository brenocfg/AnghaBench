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
 int TL_UDP_RESEND_REQUEST ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  resend_range (int /*<<< orphan*/ ,int,int,int) ; 
 int rwm_fetch_data (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

int work_resend_request (struct udp_msg *msg) {
  vkprintf (2, "work_resend_request: len = %d\n", msg->raw.total_bytes);
  if (msg->raw.total_bytes != 12) { return 0; }
  int P[3];
  assert (rwm_fetch_data (&msg->raw, P, 12) == 12);
  assert (P[0] == TL_UDP_RESEND_REQUEST);
  //vkprintf (0, "resend request: P[1] = %d, P[2] = %d\n", P[1], P[2]);
  if (P[1] > P[2]) { return 0; }
  resend_range (msg->S, P[1], P[2], 1);
  return 0;
}