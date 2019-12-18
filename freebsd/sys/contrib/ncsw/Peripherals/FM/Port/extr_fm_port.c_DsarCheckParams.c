#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_18__ {int maxNumOfArpEntries; int maxNumOfEchoIpv4Entries; scalar_t__ maxNumOfNdpEntries; int maxNumOfEchoIpv6Entries; scalar_t__ maxNumOfSnmpOidEntries; scalar_t__ maxNumOfSnmpIPV4Entries; scalar_t__ maxNumOfSnmpIPV6Entries; scalar_t__ maxNumOfIpProtFiltering; scalar_t__ maxNumOfTcpPortFiltering; scalar_t__ maxNumOfUdpPortFiltering; } ;
typedef  TYPE_12__ t_FmPortDsarTablesSizes ;
struct TYPE_19__ {TYPE_11__* p_AutoResNdpInfo; TYPE_9__* p_AutoResEchoIpv6Info; TYPE_7__* p_AutoResEchoIpv4Info; TYPE_5__* p_AutoResArpInfo; TYPE_3__* p_AutoResFilteringInfo; TYPE_2__* p_AutoResSnmpInfo; } ;
typedef  TYPE_13__ t_FmPortDsarParams ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_28__ {int tableSize; TYPE_8__* p_AutoResTable; } ;
struct TYPE_27__ {int /*<<< orphan*/  mac; } ;
struct TYPE_26__ {int tableSize; TYPE_6__* p_AutoResTable; } ;
struct TYPE_25__ {int /*<<< orphan*/  mac; } ;
struct TYPE_24__ {int tableSize; TYPE_4__* p_AutoResTable; } ;
struct TYPE_23__ {int /*<<< orphan*/  mac; } ;
struct TYPE_22__ {scalar_t__ ipProtTableSize; scalar_t__ udpPortsTableSize; scalar_t__ tcpPortsTableSize; } ;
struct TYPE_21__ {scalar_t__ oidsTblSize; scalar_t__ numOfIpv4Addresses; scalar_t__ numOfIpv6Addresses; } ;
struct TYPE_20__ {int /*<<< orphan*/  mac; } ;
struct TYPE_17__ {scalar_t__ tableSizeAssigned; scalar_t__ tableSizeTmp; TYPE_1__* p_AutoResTableTmp; TYPE_10__* p_AutoResTableAssigned; } ;
struct TYPE_16__ {int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 int FALSE ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int TRUE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static t_Error DsarCheckParams(t_FmPortDsarParams *params,
                               t_FmPortDsarTablesSizes *sizes)
{
    bool macInit = FALSE;
    uint8_t mac[6];
    int i = 0;

    // check table sizes
    if (params->p_AutoResArpInfo
            && sizes->maxNumOfArpEntries < params->p_AutoResArpInfo->tableSize)
        RETURN_ERROR(
                MAJOR, E_INVALID_VALUE,
                ("DSAR: Arp table size exceeds the configured maximum size."));
    if (params->p_AutoResEchoIpv4Info
            && sizes->maxNumOfEchoIpv4Entries
                    < params->p_AutoResEchoIpv4Info->tableSize)
        RETURN_ERROR(
                MAJOR,
                E_INVALID_VALUE,
                ("DSAR: EchoIpv4 table size exceeds the configured maximum size."));
    if (params->p_AutoResNdpInfo
            && sizes->maxNumOfNdpEntries
                    < params->p_AutoResNdpInfo->tableSizeAssigned
                            + params->p_AutoResNdpInfo->tableSizeTmp)
        RETURN_ERROR(
                MAJOR, E_INVALID_VALUE,
                ("DSAR: NDP table size exceeds the configured maximum size."));
    if (params->p_AutoResEchoIpv6Info
            && sizes->maxNumOfEchoIpv6Entries
                    < params->p_AutoResEchoIpv6Info->tableSize)
        RETURN_ERROR(
                MAJOR,
                E_INVALID_VALUE,
                ("DSAR: EchoIpv6 table size exceeds the configured maximum size."));
    if (params->p_AutoResSnmpInfo
            && sizes->maxNumOfSnmpOidEntries
                    < params->p_AutoResSnmpInfo->oidsTblSize)
        RETURN_ERROR(
                MAJOR,
                E_INVALID_VALUE,
                ("DSAR: Snmp Oid table size exceeds the configured maximum size."));
    if (params->p_AutoResSnmpInfo
            && sizes->maxNumOfSnmpIPV4Entries
                    < params->p_AutoResSnmpInfo->numOfIpv4Addresses)
        RETURN_ERROR(
                MAJOR,
                E_INVALID_VALUE,
                ("DSAR: Snmp ipv4 table size exceeds the configured maximum size."));
    if (params->p_AutoResSnmpInfo
            && sizes->maxNumOfSnmpIPV6Entries
                    < params->p_AutoResSnmpInfo->numOfIpv6Addresses)
        RETURN_ERROR(
                MAJOR,
                E_INVALID_VALUE,
                ("DSAR: Snmp ipv6 table size exceeds the configured maximum size."));
    if (params->p_AutoResFilteringInfo)
    {
        if (sizes->maxNumOfIpProtFiltering
                < params->p_AutoResFilteringInfo->ipProtTableSize)
            RETURN_ERROR(
                    MAJOR,
                    E_INVALID_VALUE,
                    ("DSAR: ip filter table size exceeds the configured maximum size."));
        if (sizes->maxNumOfTcpPortFiltering
                < params->p_AutoResFilteringInfo->udpPortsTableSize)
            RETURN_ERROR(
                    MAJOR,
                    E_INVALID_VALUE,
                    ("DSAR: udp filter table size exceeds the configured maximum size."));
        if (sizes->maxNumOfUdpPortFiltering
                < params->p_AutoResFilteringInfo->tcpPortsTableSize)
            RETURN_ERROR(
                    MAJOR,
                    E_INVALID_VALUE,
                    ("DSAR: tcp filter table size exceeds the configured maximum size."));
    }
    /* check only 1 MAC address is configured (this is what ucode currently supports) */
    if (params->p_AutoResArpInfo && params->p_AutoResArpInfo->tableSize)
    {
        memcpy(mac, params->p_AutoResArpInfo->p_AutoResTable[0].mac, 6);
        i = 1;
        macInit = TRUE;

        for (; i < params->p_AutoResArpInfo->tableSize; i++)
            if (memcmp(mac, params->p_AutoResArpInfo->p_AutoResTable[i].mac, 6))
                RETURN_ERROR(
                        MAJOR, E_INVALID_VALUE,
                        ("DSAR: Only 1 mac address is currently supported."));
    }
    if (params->p_AutoResEchoIpv4Info
            && params->p_AutoResEchoIpv4Info->tableSize)
    {
        i = 0;
        if (!macInit)
        {
            memcpy(mac, params->p_AutoResEchoIpv4Info->p_AutoResTable[0].mac,
                   6);
            i = 1;
            macInit = TRUE;
        }
        for (; i < params->p_AutoResEchoIpv4Info->tableSize; i++)
            if (memcmp(mac,
                       params->p_AutoResEchoIpv4Info->p_AutoResTable[i].mac, 6))
                RETURN_ERROR(
                        MAJOR, E_INVALID_VALUE,
                        ("DSAR: Only 1 mac address is currently supported."));
    }
    if (params->p_AutoResEchoIpv6Info
            && params->p_AutoResEchoIpv6Info->tableSize)
    {
        i = 0;
        if (!macInit)
        {
            memcpy(mac, params->p_AutoResEchoIpv6Info->p_AutoResTable[0].mac,
                   6);
            i = 1;
            macInit = TRUE;
        }
        for (; i < params->p_AutoResEchoIpv6Info->tableSize; i++)
            if (memcmp(mac,
                       params->p_AutoResEchoIpv6Info->p_AutoResTable[i].mac, 6))
                RETURN_ERROR(
                        MAJOR, E_INVALID_VALUE,
                        ("DSAR: Only 1 mac address is currently supported."));
    }
    if (params->p_AutoResNdpInfo && params->p_AutoResNdpInfo->tableSizeAssigned)
    {
        i = 0;
        if (!macInit)
        {
            memcpy(mac, params->p_AutoResNdpInfo->p_AutoResTableAssigned[0].mac,
                   6);
            i = 1;
            macInit = TRUE;
        }
        for (; i < params->p_AutoResNdpInfo->tableSizeAssigned; i++)
            if (memcmp(mac,
                       params->p_AutoResNdpInfo->p_AutoResTableAssigned[i].mac,
                       6))
                RETURN_ERROR(
                        MAJOR, E_INVALID_VALUE,
                        ("DSAR: Only 1 mac address is currently supported."));
    }
    if (params->p_AutoResNdpInfo && params->p_AutoResNdpInfo->tableSizeTmp)
    {
        i = 0;
        if (!macInit)
        {
            memcpy(mac, params->p_AutoResNdpInfo->p_AutoResTableTmp[0].mac, 6);
            i = 1;
        }
        for (; i < params->p_AutoResNdpInfo->tableSizeTmp; i++)
            if (memcmp(mac, params->p_AutoResNdpInfo->p_AutoResTableTmp[i].mac,
                       6))
                RETURN_ERROR(
                        MAJOR, E_INVALID_VALUE,
                        ("DSAR: Only 1 mac address is currently supported."));
    }
    return E_OK;
}