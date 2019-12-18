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
struct tlsv1_server {int verify_peer; } ;

/* Variables and functions */

int tlsv1_server_set_verify(struct tlsv1_server *conn, int verify_peer)
{
	conn->verify_peer = verify_peer;
	return 0;
}