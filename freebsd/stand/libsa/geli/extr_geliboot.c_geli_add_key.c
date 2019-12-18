#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  geli_ukey ;

/* Variables and functions */
 size_t GELI_MAX_KEYS ; 
 int /*<<< orphan*/  G_ELI_USERKEYLEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t nsaved_keys ; 
 int /*<<< orphan*/ * saved_keys ; 

void
geli_add_key(geli_ukey key)
{

	/*
	 * If we run out of key space, the worst that will happen is
	 * it will ask the user for the password again.
	 */
	if (nsaved_keys < GELI_MAX_KEYS) {
		memcpy(saved_keys[nsaved_keys], key, G_ELI_USERKEYLEN);
		nsaved_keys++;
	}
}