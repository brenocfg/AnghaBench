#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  nvp_stat; int /*<<< orphan*/ * nvp_nva; } ;
typedef  TYPE_1__ nvpriv_t ;
typedef  int /*<<< orphan*/  nv_alloc_t ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 

__attribute__((used)) static void
nv_priv_init(nvpriv_t *priv, nv_alloc_t *nva, uint32_t stat)
{
	bzero(priv, sizeof (nvpriv_t));

	priv->nvp_nva = nva;
	priv->nvp_stat = stat;
}