#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  stbc; int /*<<< orphan*/  OpMode; int /*<<< orphan*/  AddChan; int /*<<< orphan*/  ControlChan; } ;
struct TYPE_10__ {TYPE_2__ AddHtInfo; int /*<<< orphan*/  MacHTParamInfo; int /*<<< orphan*/  HTCapabilitiesInfo; int /*<<< orphan*/  CapInfo; int /*<<< orphan*/  HTRateBitMap; int /*<<< orphan*/  LegacyRateBitMap; } ;
struct TYPE_7__ {void* stbc; void* OpMode; int /*<<< orphan*/  AddChan; int /*<<< orphan*/  ControlChan; } ;
struct TYPE_9__ {TYPE_1__ AddHtInfo; int /*<<< orphan*/  MacHTParamInfo; void* HTCapabilitiesInfo; void* CapInfo; void* HTRateBitMap; void* LegacyRateBitMap; } ;
typedef  TYPE_3__ PeerInfo_t ;
typedef  TYPE_4__ MWL_HAL_PEERINFO ;

/* Variables and functions */
 void* htole16 (int /*<<< orphan*/ ) ; 
 void* htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cvtPeerInfo(PeerInfo_t *to, const MWL_HAL_PEERINFO *from)
{
	to->LegacyRateBitMap = htole32(from->LegacyRateBitMap);
	to->HTRateBitMap = htole32(from->HTRateBitMap);
	to->CapInfo = htole16(from->CapInfo);
	to->HTCapabilitiesInfo = htole16(from->HTCapabilitiesInfo);
	to->MacHTParamInfo = from->MacHTParamInfo;
	to->AddHtInfo.ControlChan = from->AddHtInfo.ControlChan;
	to->AddHtInfo.AddChan = from->AddHtInfo.AddChan;
	to->AddHtInfo.OpMode = htole16(from->AddHtInfo.OpMode);
	to->AddHtInfo.stbc = htole16(from->AddHtInfo.stbc);
}