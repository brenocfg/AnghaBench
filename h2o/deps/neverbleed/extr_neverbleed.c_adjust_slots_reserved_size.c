#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct key_slots {size_t reserved_size; size_t size; int /*<<< orphan*/ * bita_avail; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ecdsa_keys; int /*<<< orphan*/ * keys; } ;
struct TYPE_4__ {TYPE_1__ keys; } ;

/* Variables and functions */
 size_t BITBYTES (size_t) ; 
#define  NEVERBLEED_TYPE_ECDSA 129 
#define  NEVERBLEED_TYPE_RSA 128 
 size_t ROUND2WORD (size_t) ; 
 TYPE_2__ daemon_vars ; 
 size_t default_reserved_size ; 
 int /*<<< orphan*/  dief (char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,size_t) ; 
 void* realloc (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void adjust_slots_reserved_size(int type, struct key_slots *slots)
{
#define ROUND2WORD(n) (n + 64 - 1 - (n + 64 - 1) % 64)
    if (!slots->reserved_size || (slots->size >= slots->reserved_size)) {
        size_t size = slots->reserved_size ? ROUND2WORD((size_t)(slots->reserved_size * 0.50) + slots->reserved_size)
                : default_reserved_size;
#undef ROUND2WORD

        switch (type) {
        case NEVERBLEED_TYPE_RSA:
            if ((daemon_vars.keys.keys = realloc(daemon_vars.keys.keys, sizeof(*daemon_vars.keys.keys) * size)) == NULL)
                dief("no memory");
            break;
        case NEVERBLEED_TYPE_ECDSA:
            if ((daemon_vars.keys.ecdsa_keys = realloc(daemon_vars.keys.ecdsa_keys, sizeof(*daemon_vars.keys.ecdsa_keys) * size)) == NULL)
                dief("no memory");
            break;
        default:
            dief("invalid type adjusting reserved");
        }

        uint8_t *b;
        if ((b = realloc(slots->bita_avail, BITBYTES(size))) == NULL)
            dief("no memory");

        /* set all bits to 1 making all slots available */
        memset(&b[BITBYTES(slots->reserved_size)], 0xff, BITBYTES(size - slots->reserved_size));

        slots->bita_avail = b;
        slots->reserved_size = size;
    }
}