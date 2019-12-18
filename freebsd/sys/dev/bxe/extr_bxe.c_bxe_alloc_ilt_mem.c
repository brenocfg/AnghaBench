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
struct ecore_ilt {int dummy; } ;
struct bxe_softc {struct ecore_ilt* ilt; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_BXE_ILT ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bxe_alloc_ilt_mem(struct bxe_softc *sc)
{
    int rc = 0;

    if ((sc->ilt =
         (struct ecore_ilt *)malloc(sizeof(struct ecore_ilt),
                                    M_BXE_ILT,
                                    (M_NOWAIT | M_ZERO))) == NULL) {
        rc = 1;
    }

    return (rc);
}