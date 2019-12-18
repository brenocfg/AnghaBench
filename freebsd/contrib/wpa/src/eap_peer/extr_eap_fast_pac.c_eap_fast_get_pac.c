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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct eap_fast_pac {scalar_t__ pac_type; size_t a_id_len; struct eap_fast_pac* next; int /*<<< orphan*/  a_id; } ;

/* Variables and functions */
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

struct eap_fast_pac * eap_fast_get_pac(struct eap_fast_pac *pac_root,
				       const u8 *a_id, size_t a_id_len,
				       u16 pac_type)
{
	struct eap_fast_pac *pac = pac_root;

	while (pac) {
		if (pac->pac_type == pac_type && pac->a_id_len == a_id_len &&
		    os_memcmp(pac->a_id, a_id, a_id_len) == 0) {
			return pac;
		}
		pac = pac->next;
	}
	return NULL;
}