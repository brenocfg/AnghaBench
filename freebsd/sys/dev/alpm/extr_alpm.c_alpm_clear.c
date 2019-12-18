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
struct alpm_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALPM_SMBOUTB (struct alpm_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  SMBSTS ; 

__attribute__((used)) static int
alpm_clear(struct alpm_softc *sc)
{
	ALPM_SMBOUTB(sc, SMBSTS, 0xff);
	DELAY(10);

	return (0);
}