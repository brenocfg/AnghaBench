#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int flags; } ;
struct TYPE_15__ {TYPE_6__ generic; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;
struct TYPE_13__ {scalar_t__ curvalue; TYPE_1__ generic; } ;
struct TYPE_12__ {scalar_t__ curvalue; } ;
struct TYPE_11__ {scalar_t__ curvalue; } ;
struct TYPE_10__ {scalar_t__ curvalue; } ;
struct TYPE_16__ {scalar_t__ sfxvolume_original; scalar_t__ musicvolume_original; scalar_t__ soundSystem_original; scalar_t__ quality_original; TYPE_7__ apply; TYPE_5__ quality; TYPE_4__ soundSystem; TYPE_3__ musicvolume; TYPE_2__ sfxvolume; } ;

/* Variables and functions */
 int /*<<< orphan*/  QMF_GRAYED ; 
 int QMF_HIDDEN ; 
 int QMF_INACTIVE ; 
 scalar_t__ UISND_SDL ; 
 TYPE_8__ soundOptionsInfo ; 

__attribute__((used)) static void SoundOptions_UpdateMenuItems( void )
{
	if ( soundOptionsInfo.soundSystem.curvalue == UISND_SDL )
	{
		soundOptionsInfo.quality.generic.flags &= ~QMF_GRAYED;
	}
	else
	{
		soundOptionsInfo.quality.generic.flags |= QMF_GRAYED;
	}

	soundOptionsInfo.apply.generic.flags |= QMF_HIDDEN|QMF_INACTIVE;

	if ( soundOptionsInfo.sfxvolume_original != soundOptionsInfo.sfxvolume.curvalue )
	{
		soundOptionsInfo.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
	if ( soundOptionsInfo.musicvolume_original != soundOptionsInfo.musicvolume.curvalue )
	{
		soundOptionsInfo.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
	if ( soundOptionsInfo.soundSystem_original != soundOptionsInfo.soundSystem.curvalue )
	{
		soundOptionsInfo.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
	if ( soundOptionsInfo.quality_original != soundOptionsInfo.quality.curvalue )
	{
		soundOptionsInfo.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
}