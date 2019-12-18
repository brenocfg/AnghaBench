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
struct eap_teap_pac {struct eap_teap_pac* a_id_info; struct eap_teap_pac* i_id; struct eap_teap_pac* a_id; struct eap_teap_pac* pac_info; struct eap_teap_pac* pac_opaque; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct eap_teap_pac*) ; 

void eap_teap_free_pac(struct eap_teap_pac *pac)
{
	os_free(pac->pac_opaque);
	os_free(pac->pac_info);
	os_free(pac->a_id);
	os_free(pac->i_id);
	os_free(pac->a_id_info);
	os_free(pac);
}