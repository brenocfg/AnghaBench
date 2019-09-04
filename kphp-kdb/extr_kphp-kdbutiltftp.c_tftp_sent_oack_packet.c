#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int size; } ;
struct TYPE_5__ {TYPE_1__ file; scalar_t__ oack_size; int /*<<< orphan*/  timeout; int /*<<< orphan*/  block_size; } ;
typedef  TYPE_2__ tftp_connection_t ;

/* Variables and functions */
 char* msg_out ; 
 char* store_options (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int tftp_oack ; 

__attribute__((used)) static int tftp_sent_oack_packet (tftp_connection_t *c) {
  msg_out[0] = (tftp_oack >> 8) & 0xff;
  msg_out[1] = tftp_oack & 0xff;
  char *wptr = msg_out + 2;
  wptr = store_options (msg_out + 2, c->block_size, c->timeout, c->oack_size ? c->file.size : -1);
  return wptr - msg_out;
}