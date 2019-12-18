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
struct unl {scalar_t__ cache; scalar_t__ sock; scalar_t__ family_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct unl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nl_cache_free (scalar_t__) ; 
 int /*<<< orphan*/  nl_socket_free (scalar_t__) ; 

void unl_free(struct unl *unl)
{
	if (unl->family_name)
		free(unl->family_name);

	if (unl->sock)
		nl_socket_free(unl->sock);

	if (unl->cache)
		nl_cache_free(unl->cache);

	memset(unl, 0, sizeof(*unl));
}