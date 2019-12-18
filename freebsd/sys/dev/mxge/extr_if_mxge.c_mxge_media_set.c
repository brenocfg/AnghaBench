#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* ifm_cur; int /*<<< orphan*/  ifm_media; } ;
struct TYPE_7__ {int current_media; TYPE_4__ media; } ;
typedef  TYPE_2__ mxge_softc_t ;
struct TYPE_6__ {int /*<<< orphan*/  ifm_media; } ;

/* Variables and functions */
 int IFM_ETHER ; 
 int IFM_FDX ; 
 int /*<<< orphan*/  ifmedia_add (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_set (TYPE_4__*,int) ; 

__attribute__((used)) static void
mxge_media_set(mxge_softc_t *sc, int media_type)
{

	
	ifmedia_add(&sc->media, IFM_ETHER | IFM_FDX | media_type,
		    0, NULL);
	ifmedia_set(&sc->media, IFM_ETHER | IFM_FDX | media_type);
	sc->current_media = media_type;
	sc->media.ifm_media = sc->media.ifm_cur->ifm_media;
}