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
struct ikev2_responder_data {size_t IDi_len; int /*<<< orphan*/  IDi_type; int /*<<< orphan*/ * IDi; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_memdup (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int ikev2_process_idi(struct ikev2_responder_data *data,
			     const u8 *idi, size_t idi_len)
{
	u8 id_type;

	if (idi == NULL) {
		wpa_printf(MSG_INFO, "IKEV2: No IDi received");
		return -1;
	}

	if (idi_len < 4) {
		wpa_printf(MSG_INFO, "IKEV2: Too short IDi payload");
		return -1;
	}

	id_type = idi[0];
	idi += 4;
	idi_len -= 4;

	wpa_printf(MSG_DEBUG, "IKEV2: IDi ID Type %d", id_type);
	wpa_hexdump_ascii(MSG_DEBUG, "IKEV2: IDi", idi, idi_len);
	os_free(data->IDi);
	data->IDi = os_memdup(idi, idi_len);
	if (data->IDi == NULL)
		return -1;
	data->IDi_len = idi_len;
	data->IDi_type = id_type;

	return 0;
}