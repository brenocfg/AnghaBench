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
typedef  int /*<<< orphan*/  u64 ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UQUAD (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  sysctl_ctx_init (struct sysctl_ctx_list*) ; 

void
mlx5e_create_stats(struct sysctl_ctx_list *ctx,
    struct sysctl_oid_list *parent, const char *buffer,
    const char **desc, unsigned num, u64 * arg)
{
	struct sysctl_oid *node;
	unsigned x;

	sysctl_ctx_init(ctx);

	node = SYSCTL_ADD_NODE(ctx, parent, OID_AUTO,
	    buffer, CTLFLAG_RD, NULL, "Statistics");
	if (node == NULL)
		return;
	for (x = 0; x != num; x++) {
		SYSCTL_ADD_UQUAD(ctx, SYSCTL_CHILDREN(node), OID_AUTO,
		    desc[2 * x], CTLFLAG_RD, arg + x, desc[2 * x + 1]);
	}
}