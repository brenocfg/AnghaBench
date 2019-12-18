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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct geli_dev {size_t keybuf_slot; int /*<<< orphan*/  md; } ;

/* Variables and functions */
 scalar_t__ g_eli_mkey_decrypt_any (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nsaved_keys ; 
 int /*<<< orphan*/ * saved_keys ; 

__attribute__((used)) static int
geli_findkey(struct geli_dev *gdev, u_char *mkey)
{
	u_int keynum;
	int i;

	if (gdev->keybuf_slot >= 0) {
		if (g_eli_mkey_decrypt_any(&gdev->md, saved_keys[gdev->keybuf_slot],
		    mkey, &keynum) == 0) {
			return (0);
		}
	}

	for (i = 0; i < nsaved_keys; i++) {
		if (g_eli_mkey_decrypt_any(&gdev->md, saved_keys[i], mkey,
		    &keynum) == 0) {
			gdev->keybuf_slot = i;
			return (0);
		}
	}

	return (1);
}