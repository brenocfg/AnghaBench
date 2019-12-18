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
struct umtx_pi {int /*<<< orphan*/  pi_blocked; } ;

/* Variables and functions */
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 struct umtx_pi* uma_zalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  umtx_pi_allocated ; 
 int /*<<< orphan*/  umtx_pi_zone ; 

__attribute__((used)) static inline struct umtx_pi *
umtx_pi_alloc(int flags)
{
	struct umtx_pi *pi;

	pi = uma_zalloc(umtx_pi_zone, M_ZERO | flags);
	TAILQ_INIT(&pi->pi_blocked);
	atomic_add_int(&umtx_pi_allocated, 1);
	return (pi);
}