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
struct xencons_priv {int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * panicstr ; 

__attribute__((used)) static inline void xencons_unlock(struct xencons_priv *cons)
{

	if (panicstr == NULL)
		mtx_unlock_spin(&cons->mtx);
}