#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct keybuf {int kb_nents; TYPE_1__* kb_ents; } ;
struct TYPE_2__ {scalar_t__ ke_type; int /*<<< orphan*/  ke_data; } ;

/* Variables and functions */
 scalar_t__ KEYBUF_TYPE_GELI ; 
 scalar_t__ KEYBUF_TYPE_NONE ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ ,int) ; 
 struct keybuf* get_keybuf () ; 

__attribute__((used)) static void
zero_geli_intake_keys(void)
{
        struct keybuf *keybuf;
        int i;

        if ((keybuf = get_keybuf()) != NULL) {
                /* Scan the key buffer, clear all GELI keys. */
                for (i = 0; i < keybuf->kb_nents; i++) {
                         if (keybuf->kb_ents[i].ke_type == KEYBUF_TYPE_GELI) {
                                 explicit_bzero(keybuf->kb_ents[i].ke_data,
                                     sizeof(keybuf->kb_ents[i].ke_data));
                                 keybuf->kb_ents[i].ke_type = KEYBUF_TYPE_NONE;
                         }
                }
        }
}