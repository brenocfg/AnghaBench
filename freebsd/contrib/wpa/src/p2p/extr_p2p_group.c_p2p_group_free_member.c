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
struct p2p_group_member {int /*<<< orphan*/  client_info; int /*<<< orphan*/  p2p_ie; int /*<<< orphan*/  wfd_ie; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct p2p_group_member*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p2p_group_free_member(struct p2p_group_member *m)
{
	wpabuf_free(m->wfd_ie);
	wpabuf_free(m->p2p_ie);
	wpabuf_free(m->client_info);
	os_free(m);
}