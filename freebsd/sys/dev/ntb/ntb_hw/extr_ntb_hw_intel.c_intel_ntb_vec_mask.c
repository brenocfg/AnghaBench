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
typedef  int uint64_t ;
struct ntb_softc {int db_vec_shift; } ;

/* Variables and functions */
 scalar_t__ HAS_FEATURE (struct ntb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTB_SB01BASE_LOCKUP ; 
 int XEON_NONLINK_DB_MSIX_BITS ; 

__attribute__((used)) static inline uint64_t
intel_ntb_vec_mask(struct ntb_softc *ntb, uint64_t db_vector)
{
	uint64_t shift, mask;

	if (HAS_FEATURE(ntb, NTB_SB01BASE_LOCKUP)) {
		/*
		 * Remap vectors in custom way to make at least first
		 * three doorbells to not generate stray events.
		 * This breaks Linux compatibility (if one existed)
		 * when more then one DB is used (not by if_ntb).
		 */
		if (db_vector < XEON_NONLINK_DB_MSIX_BITS - 1)
			return (1 << db_vector);
		if (db_vector == XEON_NONLINK_DB_MSIX_BITS - 1)
			return (0x7ffc);
	}

	shift = ntb->db_vec_shift;
	mask = (1ull << shift) - 1;
	return (mask << (shift * db_vector));
}