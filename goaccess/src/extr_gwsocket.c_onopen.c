#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  WSPipeOut ;
struct TYPE_3__ {int listener; char* remote_ip; } ;
typedef  TYPE_1__ WSClient ;

/* Variables and functions */
 int INET6_ADDRSTRLEN ; 
 int WS_OPCODE_TEXT ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pack_uint32 (char*,int) ; 
 int /*<<< orphan*/  ws_write_fifo (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
onopen (WSPipeOut * pipeout, WSClient * client)
{
  uint32_t hsize = sizeof (uint32_t) * 3;
  char *hdr = calloc (hsize, sizeof (char));
  char *ptr = hdr;

  ptr += pack_uint32 (ptr, client->listener);
  ptr += pack_uint32 (ptr, WS_OPCODE_TEXT);
  ptr += pack_uint32 (ptr, INET6_ADDRSTRLEN);

  ws_write_fifo (pipeout, hdr, hsize);
  ws_write_fifo (pipeout, client->remote_ip, INET6_ADDRSTRLEN);
  free (hdr);

  return 0;
}