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
struct psycho_icarg {int /*<<< orphan*/  pica_clr; int /*<<< orphan*/  pica_sc; } ;
struct intr_vector {struct psycho_icarg* iv_icarg; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTCLR_IDLE ; 
 int /*<<< orphan*/  PSYCHO_WRITE8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
psycho_intr_clear(void *arg)
{
	struct intr_vector *iv = arg;
	struct psycho_icarg *pica = iv->iv_icarg;

	PSYCHO_WRITE8(pica->pica_sc, pica->pica_clr, INTCLR_IDLE);
}