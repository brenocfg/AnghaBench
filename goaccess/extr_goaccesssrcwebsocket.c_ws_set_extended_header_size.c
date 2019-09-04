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
typedef  int uint64_t ;

/* Variables and functions */
 int WS_FRM_PAYLOAD (char const) ; 
#define  WS_PAYLOAD_EXT16 129 
#define  WS_PAYLOAD_EXT64 128 

__attribute__((used)) static void
ws_set_extended_header_size (const char *buf, int *extended)
{
  uint64_t payloadlen = 0;
  /* determine the payload length, else read more data */
  payloadlen = WS_FRM_PAYLOAD (*(buf + 1));
  switch (payloadlen) {
  case WS_PAYLOAD_EXT16:
    *extended = 2;
    break;
  case WS_PAYLOAD_EXT64:
    *extended = 8;
    break;
  }
}