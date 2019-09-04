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
struct connection {int dummy; } ;

/* Variables and functions */
 int flush_connection_output (struct connection*) ; 
 int /*<<< orphan*/  tcp_rpcc_flush_crypto (struct connection*) ; 

int tcp_rpcc_flush_packet (struct connection *c) {
  tcp_rpcc_flush_crypto (c);
  return flush_connection_output (c);
}