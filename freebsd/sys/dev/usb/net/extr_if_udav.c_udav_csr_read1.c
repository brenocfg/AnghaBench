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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct udav_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  udav_csr_read (struct udav_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint8_t
udav_csr_read1(struct udav_softc *sc, uint16_t offset)
{
	uint8_t val;

	udav_csr_read(sc, offset, &val, 1);
	return (val);
}