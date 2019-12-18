#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  ptls_t ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ptls_raw_extension_t ;
struct TYPE_7__ {scalar_t__ (* collect_extension ) (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__) ;} ;
typedef  TYPE_2__ ptls_handshake_properties_t ;

/* Variables and functions */
 size_t MAX_UNKNOWN_EXTENSIONS ; 
 int PTLS_ALERT_ILLEGAL_PARAMETER ; 
 scalar_t__ UINT16_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ptls_iovec_init (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static int handle_unknown_extension(ptls_t *tls, ptls_handshake_properties_t *properties, uint16_t type, const uint8_t *src,
                                    const uint8_t *const end, ptls_raw_extension_t *slots)
{
    if (properties != NULL && properties->collect_extension != NULL && properties->collect_extension(tls, properties, type)) {
        size_t i;
        for (i = 0; slots[i].type != UINT16_MAX; ++i) {
            assert(i < MAX_UNKNOWN_EXTENSIONS);
            if (slots[i].type == type)
                return PTLS_ALERT_ILLEGAL_PARAMETER;
        }
        if (i < MAX_UNKNOWN_EXTENSIONS) {
            slots[i].type = type;
            slots[i].data = ptls_iovec_init(src, end - src);
            slots[i + 1].type = UINT16_MAX;
        }
    }
    return 0;
}