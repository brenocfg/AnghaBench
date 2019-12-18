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
struct radius_client_data {int auth_sock; int auth_serv_sock; int auth_serv_sock6; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  eloop_unregister_read_sock (int) ; 

__attribute__((used)) static void radius_close_auth_sockets(struct radius_client_data *radius)
{
	radius->auth_sock = -1;

	if (radius->auth_serv_sock >= 0) {
		eloop_unregister_read_sock(radius->auth_serv_sock);
		close(radius->auth_serv_sock);
		radius->auth_serv_sock = -1;
	}
#ifdef CONFIG_IPV6
	if (radius->auth_serv_sock6 >= 0) {
		eloop_unregister_read_sock(radius->auth_serv_sock6);
		close(radius->auth_serv_sock6);
		radius->auth_serv_sock6 = -1;
	}
#endif /* CONFIG_IPV6 */
}