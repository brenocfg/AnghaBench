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
struct schizo_icarg {int /*<<< orphan*/  sica_map; int /*<<< orphan*/  sica_sc; } ;
struct intr_vector {int /*<<< orphan*/  iv_mid; struct schizo_icarg* iv_icarg; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTMAP_TID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCHIZO_PCI_READ_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCHIZO_PCI_WRITE_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
schizo_intr_assign(void *arg)
{
	struct intr_vector *iv = arg;
	struct schizo_icarg *sica = iv->iv_icarg;

	SCHIZO_PCI_WRITE_8(sica->sica_sc, sica->sica_map, INTMAP_TID(
	    SCHIZO_PCI_READ_8(sica->sica_sc, sica->sica_map), iv->iv_mid));
}