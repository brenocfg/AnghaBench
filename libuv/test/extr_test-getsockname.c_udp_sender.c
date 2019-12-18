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
typedef  int /*<<< orphan*/  uv_buf_t ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  send_req ; 
 int /*<<< orphan*/  server_port ; 
 int /*<<< orphan*/  udp ; 
 int /*<<< orphan*/  udp_send ; 
 int /*<<< orphan*/  uv_buf_init (char*,int) ; 
 scalar_t__ uv_ip4_addr (char*,int /*<<< orphan*/ ,struct sockaddr_in*) ; 
 int uv_udp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uv_udp_send (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct sockaddr const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udp_sender(void) {
  struct sockaddr_in server_addr;
  uv_buf_t buf;
  int r;

  r = uv_udp_init(loop, &udp);
  ASSERT(!r);

  buf = uv_buf_init("PING", 4);
  ASSERT(0 == uv_ip4_addr("127.0.0.1", server_port, &server_addr));

  r = uv_udp_send(&send_req,
                  &udp,
                  &buf,
                  1,
                  (const struct sockaddr*) &server_addr,
                  udp_send);
  ASSERT(!r);
}