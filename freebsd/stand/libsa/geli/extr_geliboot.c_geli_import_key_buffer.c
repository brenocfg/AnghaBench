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
struct keybuf {unsigned int kb_nents; TYPE_1__* kb_ents; } ;
struct TYPE_2__ {int /*<<< orphan*/  ke_type; int /*<<< orphan*/  ke_data; } ;

/* Variables and functions */
 unsigned int GELI_MAX_KEYS ; 
 int /*<<< orphan*/  G_ELI_USERKEYLEN ; 
 int /*<<< orphan*/  KEYBUF_TYPE_NONE ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int nsaved_keys ; 
 int /*<<< orphan*/ * saved_keys ; 

void
geli_import_key_buffer(struct keybuf *skeybuf)
{
	unsigned int i;

	for (i = 0; i < skeybuf->kb_nents && i < GELI_MAX_KEYS; i++) {
		memcpy(saved_keys[i], skeybuf->kb_ents[i].ke_data,
		    G_ELI_USERKEYLEN);
		explicit_bzero(skeybuf->kb_ents[i].ke_data,
		    G_ELI_USERKEYLEN);
		skeybuf->kb_ents[i].ke_type = KEYBUF_TYPE_NONE;
	}
	nsaved_keys = skeybuf->kb_nents;
	skeybuf->kb_nents = 0;
}