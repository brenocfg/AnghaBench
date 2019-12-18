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
struct peer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct peer*,int /*<<< orphan*/ ) ; 
 struct peer* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  pqueue ; 

__attribute__((used)) static int
addpeer(struct peer *pe0)
{
	struct peer *pe;

	pe = calloc(1, sizeof(*pe));
	if (pe == NULL)
		err(1, "malloc failed");
	*pe = *pe0;
	STAILQ_INSERT_TAIL(&pqueue, pe, next);

	return (0);
}