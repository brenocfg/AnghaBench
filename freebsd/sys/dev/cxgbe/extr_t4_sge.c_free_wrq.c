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
struct sge_wrq {int /*<<< orphan*/  eq; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct sge_wrq*,int) ; 
 int free_eq (struct adapter*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
free_wrq(struct adapter *sc, struct sge_wrq *wrq)
{
	int rc;

	rc = free_eq(sc, &wrq->eq);
	if (rc)
		return (rc);

	bzero(wrq, sizeof(*wrq));
	return (0);
}