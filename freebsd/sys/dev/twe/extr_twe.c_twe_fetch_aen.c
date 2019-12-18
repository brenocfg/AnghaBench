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
struct twe_softc {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  TWE_PARAM_AEN ; 
 int /*<<< orphan*/  TWE_PARAM_AEN_UnitCode ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/ * twe_get_param (struct twe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twe_handle_aen ; 

__attribute__((used)) static int
twe_fetch_aen(struct twe_softc *sc)
{

    debug_called(4);

    if ((twe_get_param(sc, TWE_PARAM_AEN, TWE_PARAM_AEN_UnitCode, 2, twe_handle_aen)) == NULL)
	return(EIO);
    return(0);
}