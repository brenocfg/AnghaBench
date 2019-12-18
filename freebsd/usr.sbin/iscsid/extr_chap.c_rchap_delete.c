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
struct rchap {struct rchap* rchap_challenge; struct rchap* rchap_secret; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct rchap*) ; 

void
rchap_delete(struct rchap *rchap)
{

	free(rchap->rchap_secret);
	free(rchap->rchap_challenge);
	free(rchap);
}