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
struct ggd_connection {int c_sendfd; int c_recvfd; } ;

/* Variables and functions */

__attribute__((used)) static int
connection_ready(struct ggd_connection *conn)
{

	return (conn->c_sendfd != -1 && conn->c_recvfd != -1);
}