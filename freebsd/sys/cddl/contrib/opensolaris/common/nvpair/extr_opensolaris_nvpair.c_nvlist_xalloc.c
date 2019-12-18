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
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  nvpriv_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  nv_alloc_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NV_ALIGN (int) ; 
 int /*<<< orphan*/  nv_mem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * nv_mem_zalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nv_priv_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
nvlist_xalloc(nvlist_t **nvlp, uint_t nvflag, nv_alloc_t *nva)
{
	nvpriv_t *priv;

	if (nvlp == NULL || nva == NULL)
		return (EINVAL);

	if ((priv = nv_priv_alloc(nva)) == NULL)
		return (ENOMEM);

	if ((*nvlp = nv_mem_zalloc(priv,
	    NV_ALIGN(sizeof (nvlist_t)))) == NULL) {
		nv_mem_free(priv, priv, sizeof (nvpriv_t));
		return (ENOMEM);
	}

	nvlist_init(*nvlp, nvflag, priv);

	return (0);
}