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
struct upa_icarg {int /*<<< orphan*/  uica_imr; int /*<<< orphan*/  uica_sc; } ;
struct intr_vector {int /*<<< orphan*/  iv_mid; int /*<<< orphan*/  iv_vec; struct upa_icarg* iv_icarg; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTMAP_ENABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPA_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UPA_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
upa_intr_enable(void *arg)
{
	struct intr_vector *iv = arg;
	struct upa_icarg *uica = iv->iv_icarg;

	UPA_WRITE(uica->uica_sc, uica->uica_imr, 0x0,
	    INTMAP_ENABLE(iv->iv_vec, iv->iv_mid));
	(void)UPA_READ(uica->uica_sc, uica->uica_imr, 0x0);
}