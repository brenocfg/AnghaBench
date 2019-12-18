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
struct sysctl_ctx_list {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TAILQ_INIT (struct sysctl_ctx_list*) ; 

int
sysctl_ctx_init(struct sysctl_ctx_list *c)
{

	if (c == NULL) {
		return (EINVAL);
	}

	/*
	 * No locking here, the caller is responsible for not adding
	 * new nodes to a context until after this function has
	 * returned.
	 */
	TAILQ_INIT(c);
	return (0);
}