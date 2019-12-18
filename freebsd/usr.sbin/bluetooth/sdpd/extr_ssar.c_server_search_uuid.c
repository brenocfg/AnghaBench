#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint128_t ;
typedef  TYPE_2__* provider_p ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_7__ {int (* create ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ;} ;
typedef  TYPE_3__ attr_t ;
struct TYPE_6__ {TYPE_1__* profile; } ;
struct TYPE_5__ {TYPE_3__* attrs; } ;

/* Variables and functions */
 scalar_t__ server_search_uuid_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int
server_search_uuid(provider_p const provider, const uint128_t *uuid)
{
        uint8_t buffer[256];
        const attr_t *attr;
        int len;

        for (attr = provider->profile->attrs; attr->create != NULL; attr++) {

                len = attr->create(buffer, buffer + sizeof(buffer),
                    (const uint8_t *)provider->profile, sizeof(*provider->profile));
                if (len < 0)
                        continue;
                if (server_search_uuid_sub(buffer, buffer + len, uuid) == 0)
                        return (0);
        }
        return (1);
}