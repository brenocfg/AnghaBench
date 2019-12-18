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
struct tlsv1_server {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct tlsv1_server*) ; 
 int /*<<< orphan*/  tlsv1_server_clear_data (struct tlsv1_server*) ; 

void tlsv1_server_deinit(struct tlsv1_server *conn)
{
	tlsv1_server_clear_data(conn);
	os_free(conn);
}