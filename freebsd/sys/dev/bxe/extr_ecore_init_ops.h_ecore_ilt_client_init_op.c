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
struct ilt_client_info {int dummy; } ;
struct ecore_ilt {int dummy; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 struct ecore_ilt* SC_ILT (struct bxe_softc*) ; 
 int /*<<< orphan*/  ecore_ilt_client_init_op_ilt (struct bxe_softc*,struct ecore_ilt*,struct ilt_client_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_ilt_client_init_op(struct bxe_softc *sc,
				     struct ilt_client_info *ilt_cli, uint8_t initop)
{
	struct ecore_ilt *ilt = SC_ILT(sc);

	ecore_ilt_client_init_op_ilt(sc, ilt, ilt_cli, initop);
}