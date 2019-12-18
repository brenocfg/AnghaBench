#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int last_block; int last_block_len; } ;
typedef  TYPE_1__ tftp_connection_t ;

/* Variables and functions */
 int* msg_out ; 
 int tftp_block_read (TYPE_1__*,int,int*) ; 
 int tftp_data ; 
 int tftp_store_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tftp_undef ; 

__attribute__((used)) static int tftp_sent_data_packet (tftp_connection_t *c, int block) {
  //int r = tftp_pread (c->F, msg_out + 4, c->block_size, (block - 1) * c->block_size);
  int r = tftp_block_read (c, block, msg_out + 4);
  if (r < 0) {
    return tftp_store_error (tftp_undef, "IO error: Read failed");
  }
  msg_out[0] = (tftp_data >> 8) & 0xff;
  msg_out[1] = tftp_data & 0xff;
  msg_out[2] = (block >> 8) & 0xff;
  msg_out[3] = block & 0xff;
  c->last_block = block;
  c->last_block_len = r;
  return r + 4;
}