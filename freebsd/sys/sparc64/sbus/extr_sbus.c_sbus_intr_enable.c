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
struct sbus_icarg {int /*<<< orphan*/  sica_map; int /*<<< orphan*/  sica_sc; } ;
struct intr_vector {int /*<<< orphan*/  iv_mid; int /*<<< orphan*/  iv_vec; struct sbus_icarg* iv_icarg; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTMAP_ENABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSIO_WRITE8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sbus_intr_enable(void *arg)
{
	struct intr_vector *iv = arg;
	struct sbus_icarg *sica = iv->iv_icarg;

	SYSIO_WRITE8(sica->sica_sc, sica->sica_map,
	    INTMAP_ENABLE(iv->iv_vec, iv->iv_mid));
}