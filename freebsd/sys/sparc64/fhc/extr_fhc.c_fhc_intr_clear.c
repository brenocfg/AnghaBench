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
struct intr_vector {struct fhc_icarg* iv_icarg; } ;
struct fhc_icarg {int /*<<< orphan*/  fica_memres; } ;

/* Variables and functions */
 int /*<<< orphan*/  FHC_ICLR ; 
 int /*<<< orphan*/  INTCLR_IDLE ; 
 int /*<<< orphan*/  bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fhc_intr_clear(void *arg)
{
	struct intr_vector *iv = arg;
	struct fhc_icarg *fica = iv->iv_icarg;

	bus_write_4(fica->fica_memres, FHC_ICLR, INTCLR_IDLE);
	(void)bus_read_4(fica->fica_memres, FHC_ICLR);
}