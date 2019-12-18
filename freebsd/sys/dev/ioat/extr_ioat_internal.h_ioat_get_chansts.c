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
typedef  int /*<<< orphan*/  uint64_t ;
struct ioat_softc {scalar_t__ version; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOAT_CHANSTS_OFFSET ; 
 scalar_t__ IOAT_VER_3_3 ; 
 int /*<<< orphan*/  ioat_read_8 (struct ioat_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioat_read_double_4 (struct ioat_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint64_t
ioat_get_chansts(struct ioat_softc *ioat)
{
	uint64_t status;

	if (ioat->version >= IOAT_VER_3_3)
		status = ioat_read_8(ioat, IOAT_CHANSTS_OFFSET);
	else
		/* Must read lower 4 bytes before upper 4 bytes. */
		status = ioat_read_double_4(ioat, IOAT_CHANSTS_OFFSET);
	return (status);
}