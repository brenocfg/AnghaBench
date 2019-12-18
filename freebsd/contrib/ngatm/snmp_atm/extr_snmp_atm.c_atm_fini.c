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
struct atmif_priv {int dummy; } ;

/* Variables and functions */
 struct atmif_priv* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atmif_destroy (struct atmif_priv*) ; 
 int /*<<< orphan*/  atmif_list ; 
 int /*<<< orphan*/  mib_unregister_newif (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module ; 
 int /*<<< orphan*/  or_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_atm ; 

__attribute__((used)) static int
atm_fini(void)
{
	struct atmif_priv *aif;

	while ((aif = TAILQ_FIRST(&atmif_list)) != NULL)
		atmif_destroy(aif);

	mib_unregister_newif(module);
	or_unregister(reg_atm);

	return (0);
}