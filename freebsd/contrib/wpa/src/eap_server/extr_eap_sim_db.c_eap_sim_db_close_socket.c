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
struct eap_sim_db_data {int sock; int /*<<< orphan*/ * local_sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  eloop_unregister_read_sock (int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void eap_sim_db_close_socket(struct eap_sim_db_data *data)
{
	if (data->sock >= 0) {
		eloop_unregister_read_sock(data->sock);
		close(data->sock);
		data->sock = -1;
	}
	if (data->local_sock) {
		unlink(data->local_sock);
		os_free(data->local_sock);
		data->local_sock = NULL;
	}
}