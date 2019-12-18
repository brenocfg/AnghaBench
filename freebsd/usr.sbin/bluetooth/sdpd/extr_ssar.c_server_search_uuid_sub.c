#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int const uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint128_t ;
struct TYPE_5__ {int* b; } ;
typedef  TYPE_1__ int128_t ;
typedef  int /*<<< orphan*/  duuid ;

/* Variables and functions */
#define  SDP_DATA_BOOL 147 
#define  SDP_DATA_INT128 146 
#define  SDP_DATA_INT16 145 
#define  SDP_DATA_INT32 144 
#define  SDP_DATA_INT64 143 
#define  SDP_DATA_INT8 142 
#define  SDP_DATA_SEQ16 141 
#define  SDP_DATA_SEQ32 140 
#define  SDP_DATA_SEQ8 139 
#define  SDP_DATA_STR16 138 
#define  SDP_DATA_STR32 137 
#define  SDP_DATA_STR8 136 
#define  SDP_DATA_UINT128 135 
#define  SDP_DATA_UINT16 134 
#define  SDP_DATA_UINT32 133 
#define  SDP_DATA_UINT64 132 
#define  SDP_DATA_UINT8 131 
#define  SDP_DATA_UUID128 130 
#define  SDP_DATA_UUID16 129 
#define  SDP_DATA_UUID32 128 
 int /*<<< orphan*/  SDP_GET16 (int,int const*) ; 
 int /*<<< orphan*/  SDP_GET32 (int,int const*) ; 
 int /*<<< orphan*/  SDP_GET8 (int const,int const*) ; 
 int /*<<< orphan*/  SDP_GET_UUID128 (TYPE_1__*,int const*) ; 
 int /*<<< orphan*/  memcmp (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uuid_base ; 

__attribute__((used)) static int
server_search_uuid_sub(uint8_t *buf, uint8_t const * const eob, const uint128_t *uuid)
{
        int128_t duuid;
        uint32_t value;
        uint8_t type;

        while (buf < eob) {

                SDP_GET8(type, buf);

                switch (type) {
                case SDP_DATA_UUID16:
                        if (buf + 2 > eob)
                                continue;
                        SDP_GET16(value, buf);

                        memcpy(&duuid, &uuid_base, sizeof(duuid));
                        duuid.b[2] = value >> 8 & 0xff;
                        duuid.b[3] = value & 0xff;

                        if (memcmp(&duuid, uuid, sizeof(duuid)) == 0)
                                return (0);
                        break;
                case SDP_DATA_UUID32:
                        if (buf + 4 > eob)
                                continue;
                        SDP_GET32(value, buf);
                        memcpy(&duuid, &uuid_base, sizeof(duuid));
                        duuid.b[0] = value >> 24 & 0xff;
                        duuid.b[1] = value >> 16 & 0xff;
                        duuid.b[2] = value >> 8 & 0xff;
                        duuid.b[3] = value & 0xff;

                        if (memcmp(&duuid, uuid, sizeof(duuid)) == 0)
                                return (0);
                        break;
                case SDP_DATA_UUID128:
                        if (buf + 16 > eob)
                                continue;
                        SDP_GET_UUID128(&duuid, buf);

                        if (memcmp(&duuid, uuid, sizeof(duuid)) == 0)
                                return (0);
                        break;
                case SDP_DATA_UINT8:
                case SDP_DATA_INT8:
                case SDP_DATA_SEQ8:
                        buf++;
                        break;
                case SDP_DATA_UINT16:
                case SDP_DATA_INT16:
                case SDP_DATA_SEQ16:
                        buf += 2;
                        break;
                case SDP_DATA_UINT32:
                case SDP_DATA_INT32:
                case SDP_DATA_SEQ32:
                        buf += 4;
                        break;
                case SDP_DATA_UINT64:
                case SDP_DATA_INT64:
                        buf += 8;
                        break;
                case SDP_DATA_UINT128:
                case SDP_DATA_INT128:
                        buf += 16;
                        break;
                case SDP_DATA_STR8:
                        if (buf + 1 > eob)
                                continue;
                        SDP_GET8(value, buf);
                        buf += value;
                        break;
                case SDP_DATA_STR16:
                        if (buf + 2 > eob)
                                continue;
                        SDP_GET16(value, buf);
                        if (value > (eob - buf))
                                return (1);
                        buf += value;
                        break;
                case SDP_DATA_STR32:
                        if (buf + 4 > eob)
                                continue;
                        SDP_GET32(value, buf);
                        if (value > (eob - buf))
                                return (1);
                        buf += value;
                        break;
                case SDP_DATA_BOOL:
                        buf += 1;
                        break;
                default:
                        return (1);
                }
        }
        return (1);
}