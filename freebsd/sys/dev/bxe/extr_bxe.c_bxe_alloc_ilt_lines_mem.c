#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ilt_line {int dummy; } ;
struct bxe_softc {TYPE_1__* ilt; } ;
struct TYPE_2__ {struct ilt_line* lines; } ;

/* Variables and functions */
 int ILT_MAX_LINES ; 
 int /*<<< orphan*/  M_BXE_ILT ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bxe_alloc_ilt_lines_mem(struct bxe_softc *sc)
{
    int rc = 0;

    if ((sc->ilt->lines =
         (struct ilt_line *)malloc((sizeof(struct ilt_line) * ILT_MAX_LINES),
                                    M_BXE_ILT,
                                    (M_NOWAIT | M_ZERO))) == NULL) {
        rc = 1;
    }

    return (rc);
}