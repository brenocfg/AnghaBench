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
struct csession {struct csession* mackey; struct csession* key; int /*<<< orphan*/  lock; int /*<<< orphan*/  cses; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_XDATA ; 
 int /*<<< orphan*/  crypto_freesession (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct csession*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
csefree(struct csession *cse)
{

	crypto_freesession(cse->cses);
	mtx_destroy(&cse->lock);
	if (cse->key)
		free(cse->key, M_XDATA);
	if (cse->mackey)
		free(cse->mackey, M_XDATA);
	free(cse, M_XDATA);
}