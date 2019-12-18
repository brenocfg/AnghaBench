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
typedef  unsigned int u16 ;
struct eap_fast_pac {int pac_info_len; unsigned int a_id_len; unsigned int a_id_info_len; int /*<<< orphan*/ * a_id_info; int /*<<< orphan*/ * a_id; int /*<<< orphan*/ * pac_info; } ;

/* Variables and functions */
 unsigned int PAC_TYPE_A_ID ; 
 unsigned int PAC_TYPE_A_ID_INFO ; 
 unsigned int WPA_GET_BE16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 void* os_memdup (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void eap_fast_pac_get_a_id(struct eap_fast_pac *pac)
{
	u8 *pos, *end;
	u16 type, len;

	pos = pac->pac_info;
	end = pos + pac->pac_info_len;

	while (end - pos > 4) {
		type = WPA_GET_BE16(pos);
		pos += 2;
		len = WPA_GET_BE16(pos);
		pos += 2;
		if (len > (unsigned int) (end - pos))
			break;

		if (type == PAC_TYPE_A_ID) {
			os_free(pac->a_id);
			pac->a_id = os_memdup(pos, len);
			if (pac->a_id == NULL)
				break;
			pac->a_id_len = len;
		}

		if (type == PAC_TYPE_A_ID_INFO) {
			os_free(pac->a_id_info);
			pac->a_id_info = os_memdup(pos, len);
			if (pac->a_id_info == NULL)
				break;
			pac->a_id_info_len = len;
		}

		pos += len;
	}
}