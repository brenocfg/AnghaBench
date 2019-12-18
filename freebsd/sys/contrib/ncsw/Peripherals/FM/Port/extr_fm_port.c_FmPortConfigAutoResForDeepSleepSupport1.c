#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  t_PortTblEntry ;
typedef  int /*<<< orphan*/  t_OidsTblEntry ;
struct TYPE_10__ {int maxNumOfArpEntries; int maxNumOfEchoIpv4Entries; int maxNumOfEchoIpv6Entries; int maxNumOfNdpEntries; int maxNumOfSnmpIPV4Entries; int maxNumOfSnmpIPV6Entries; int maxNumOfSnmpOidEntries; int maxNumOfUdpPortFiltering; int maxNumOfTcpPortFiltering; scalar_t__ maxNumOfIpProtFiltering; scalar_t__ maxNumOfSnmpOidChar; } ;
typedef  TYPE_4__ t_FmPortDsarTablesSizes ;
struct TYPE_7__ {TYPE_4__* autoResMaxSizes; } ;
struct TYPE_11__ {scalar_t__ fmMuramPhysBaseAddr; TYPE_3__* p_FmPortBmiRegs; int /*<<< orphan*/  h_FmMuram; TYPE_1__ deepSleepVars; } ;
typedef  TYPE_5__ t_FmPort ;
typedef  int /*<<< orphan*/  t_Error ;
typedef  int /*<<< orphan*/  t_DsarSnmpIpv6AddrTblEntry ;
typedef  int /*<<< orphan*/  t_DsarSnmpIpv4AddrTblEntry ;
typedef  int /*<<< orphan*/  t_DsarSnmpDescriptor ;
typedef  int /*<<< orphan*/  t_DsarNdDescriptor ;
typedef  int /*<<< orphan*/  t_DsarIcmpV6Statistics ;
typedef  int /*<<< orphan*/  t_DsarIcmpV6Descriptor ;
typedef  int /*<<< orphan*/  t_DsarIcmpV6BindingEntry ;
typedef  int /*<<< orphan*/  t_DsarIcmpV4Statistics ;
typedef  int /*<<< orphan*/  t_DsarIcmpV4Descriptor ;
typedef  int /*<<< orphan*/  t_DsarIcmpV4BindingEntry ;
typedef  int /*<<< orphan*/  t_DsarArpStatistics ;
typedef  int /*<<< orphan*/  t_DsarArpDescriptor ;
typedef  int /*<<< orphan*/  t_DsarArpBindingEntry ;
typedef  int /*<<< orphan*/  t_ArStatistics ;
typedef  int /*<<< orphan*/  t_ArCommonDesc ;
struct TYPE_8__ {int /*<<< orphan*/  fmbm_rgpr; } ;
struct TYPE_9__ {TYPE_2__ rxPortBmiRegs; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/ * FM_MURAM_AllocMem (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ GET_UINT32 (int /*<<< orphan*/ ) ; 
 int ROUND_UP (int,int) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int,int) ; 
 int* XX_PhysToVirt (scalar_t__) ; 
 scalar_t__ XX_VirtToPhys (int /*<<< orphan*/ *) ; 

__attribute__((used)) static t_Error FmPortConfigAutoResForDeepSleepSupport1(t_FmPort *p_FmPort)
{
    uint32_t *param_page;
    t_FmPortDsarTablesSizes *params = p_FmPort->deepSleepVars.autoResMaxSizes;
    t_ArCommonDesc *ArCommonDescPtr;
    uint32_t size = sizeof(t_ArCommonDesc);
    // ARP
    // should put here if (params->max_num_of_arp_entries)?
    size = ROUND_UP(size,4);
    size += sizeof(t_DsarArpDescriptor);
    size += sizeof(t_DsarArpBindingEntry) * params->maxNumOfArpEntries;
    size += sizeof(t_DsarArpStatistics);
    //ICMPV4
    size = ROUND_UP(size,4);
    size += sizeof(t_DsarIcmpV4Descriptor);
    size += sizeof(t_DsarIcmpV4BindingEntry) * params->maxNumOfEchoIpv4Entries;
    size += sizeof(t_DsarIcmpV4Statistics);
    //ICMPV6
    size = ROUND_UP(size,4);
    size += sizeof(t_DsarIcmpV6Descriptor);
    size += sizeof(t_DsarIcmpV6BindingEntry) * params->maxNumOfEchoIpv6Entries;
    size += sizeof(t_DsarIcmpV6Statistics);
    //ND
    size = ROUND_UP(size,4);
    size += sizeof(t_DsarNdDescriptor);
    size += sizeof(t_DsarIcmpV6BindingEntry) * params->maxNumOfNdpEntries;
    size += sizeof(t_DsarIcmpV6Statistics);
    //SNMP
    size = ROUND_UP(size,4);
    size += sizeof(t_DsarSnmpDescriptor);
    size += sizeof(t_DsarSnmpIpv4AddrTblEntry)
            * params->maxNumOfSnmpIPV4Entries;
    size += sizeof(t_DsarSnmpIpv6AddrTblEntry)
            * params->maxNumOfSnmpIPV6Entries;
    size += sizeof(t_OidsTblEntry) * params->maxNumOfSnmpOidEntries;
    size += params->maxNumOfSnmpOidChar;
    size += sizeof(t_DsarIcmpV6Statistics);
    //filters
    size = ROUND_UP(size,4);
    size += params->maxNumOfIpProtFiltering;
    size = ROUND_UP(size,4);
    size += params->maxNumOfUdpPortFiltering * sizeof(t_PortTblEntry);
    size = ROUND_UP(size,4);
    size += params->maxNumOfTcpPortFiltering * sizeof(t_PortTblEntry);

    // add here for more protocols

    // statistics
    size = ROUND_UP(size,4);
    size += sizeof(t_ArStatistics);

    ArCommonDescPtr = FM_MURAM_AllocMem(p_FmPort->h_FmMuram, size, 0x10);

    param_page =
            XX_PhysToVirt(
                    p_FmPort->fmMuramPhysBaseAddr
                            + GET_UINT32(p_FmPort->p_FmPortBmiRegs->rxPortBmiRegs.fmbm_rgpr));
    WRITE_UINT32(
            *param_page,
            (uint32_t)(XX_VirtToPhys(ArCommonDescPtr) - p_FmPort->fmMuramPhysBaseAddr));
    return E_OK;
}