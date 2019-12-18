#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cyapa_cdevpriv {TYPE_1__* sc; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_CYAPA ; 
 int /*<<< orphan*/  cyapa_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  cyapa_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  free (struct cyapa_cdevpriv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cyapa_cdevpriv_dtor(void *data)
{
	struct cyapa_cdevpriv *priv;

	priv = data;
	KASSERT(priv != NULL, ("cyapa cdevpriv should not be NULL!"));

	cyapa_lock(priv->sc);
	priv->sc->count--;
	cyapa_unlock(priv->sc);

	free(priv, M_CYAPA);
}