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
struct umtx_pi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct umtx_pi*) ; 
 int /*<<< orphan*/  umtx_pi_allocated ; 
 int /*<<< orphan*/  umtx_pi_zone ; 

__attribute__((used)) static inline void
umtx_pi_free(struct umtx_pi *pi)
{
	uma_zfree(umtx_pi_zone, pi);
	atomic_add_int(&umtx_pi_allocated, -1);
}