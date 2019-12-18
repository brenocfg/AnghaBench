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
struct unl {int /*<<< orphan*/  family; int /*<<< orphan*/  cache; int /*<<< orphan*/  sock; int /*<<< orphan*/  family_name; int /*<<< orphan*/  hdrlen; } ;
struct genlmsghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLMSG_ALIGN (int) ; 
 scalar_t__ genl_connect (int /*<<< orphan*/ ) ; 
 scalar_t__ genl_ctrl_alloc_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  genl_ctrl_search_by_name (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  memset (struct unl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  unl_free (struct unl*) ; 
 scalar_t__ unl_init (struct unl*) ; 

int unl_genl_init(struct unl *unl, const char *family)
{
	memset(unl, 0, sizeof(*unl));

	if (unl_init(unl))
		goto error_out;

	unl->hdrlen = NLMSG_ALIGN(sizeof(struct genlmsghdr));
	unl->family_name = strdup(family);
	if (!unl->family_name)
		goto error;

	if (genl_connect(unl->sock))
		goto error;

	if (genl_ctrl_alloc_cache(unl->sock, &unl->cache))
		goto error;

	unl->family = genl_ctrl_search_by_name(unl->cache, family);
	if (!unl->family)
		goto error;

	return 0;

error:
	unl_free(unl);
error_out:
	return -1;
}