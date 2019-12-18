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
struct uchcom_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  uchcom_convert_status (struct uchcom_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uchcom_get_status (struct uchcom_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
uchcom_update_status(struct uchcom_softc *sc)
{
	uint8_t cur;

	uchcom_get_status(sc, &cur);
	uchcom_convert_status(sc, cur);
}