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
struct rsa_mpi_key {int /*<<< orphan*/  n; int /*<<< orphan*/  d; } ;
typedef  int /*<<< orphan*/  MPI ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ mpi_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mpi_cmp_ui (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mpi_powm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _rsa_dec(const struct rsa_mpi_key *key, MPI m, MPI c)
{
	/* (1) Validate 0 <= c < n */
	if (mpi_cmp_ui(c, 0) < 0 || mpi_cmp(c, key->n) >= 0)
		return -EINVAL;

	/* (2) m = c^d mod n */
	return mpi_powm(m, c, key->d, key->n);
}