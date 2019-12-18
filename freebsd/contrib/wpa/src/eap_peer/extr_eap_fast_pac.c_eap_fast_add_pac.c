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
struct eap_fast_pac {struct eap_fast_pac* next; int /*<<< orphan*/  a_id_info_len; int /*<<< orphan*/ * a_id_info; int /*<<< orphan*/  i_id_len; int /*<<< orphan*/ * i_id; int /*<<< orphan*/  a_id_len; int /*<<< orphan*/ * a_id; int /*<<< orphan*/  pac_info_len; int /*<<< orphan*/ * pac_info; int /*<<< orphan*/  pac_opaque_len; int /*<<< orphan*/ * pac_opaque; int /*<<< orphan*/  pac_key; int /*<<< orphan*/  pac_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_FAST_PAC_KEY_LEN ; 
 scalar_t__ eap_fast_copy_buf (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_fast_free_pac (struct eap_fast_pac*) ; 
 int /*<<< orphan*/  eap_fast_remove_pac (struct eap_fast_pac**,struct eap_fast_pac**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct eap_fast_pac* os_zalloc (int) ; 

int eap_fast_add_pac(struct eap_fast_pac **pac_root,
		     struct eap_fast_pac **pac_current,
		     struct eap_fast_pac *entry)
{
	struct eap_fast_pac *pac;

	if (entry == NULL || entry->a_id == NULL)
		return -1;

	/* Remove a possible old entry for the matching A-ID. */
	eap_fast_remove_pac(pac_root, pac_current,
			    entry->a_id, entry->a_id_len, entry->pac_type);

	/* Allocate a new entry and add it to the list of PACs. */
	pac = os_zalloc(sizeof(*pac));
	if (pac == NULL)
		return -1;

	pac->pac_type = entry->pac_type;
	os_memcpy(pac->pac_key, entry->pac_key, EAP_FAST_PAC_KEY_LEN);
	if (eap_fast_copy_buf(&pac->pac_opaque, &pac->pac_opaque_len,
			      entry->pac_opaque, entry->pac_opaque_len) < 0 ||
	    eap_fast_copy_buf(&pac->pac_info, &pac->pac_info_len,
			      entry->pac_info, entry->pac_info_len) < 0 ||
	    eap_fast_copy_buf(&pac->a_id, &pac->a_id_len,
			      entry->a_id, entry->a_id_len) < 0 ||
	    eap_fast_copy_buf(&pac->i_id, &pac->i_id_len,
			      entry->i_id, entry->i_id_len) < 0 ||
	    eap_fast_copy_buf(&pac->a_id_info, &pac->a_id_info_len,
			      entry->a_id_info, entry->a_id_info_len) < 0) {
		eap_fast_free_pac(pac);
		return -1;
	}

	pac->next = *pac_root;
	*pac_root = pac;

	return 0;
}