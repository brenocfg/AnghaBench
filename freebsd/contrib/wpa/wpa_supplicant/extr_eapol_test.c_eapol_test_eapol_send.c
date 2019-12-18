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

/* Variables and functions */
 int IEEE802_1X_TYPE_EAP_PACKET ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eapol_test ; 
 int /*<<< orphan*/  ieee802_1x_encapsulate_radius (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  printf (char*,int,unsigned long) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int eapol_test_eapol_send(void *ctx, int type, const u8 *buf,
				 size_t len)
{
	printf("WPA: eapol_test_eapol_send(type=%d len=%lu)\n",
	       type, (unsigned long) len);
	if (type == IEEE802_1X_TYPE_EAP_PACKET) {
		wpa_hexdump(MSG_DEBUG, "TX EAP -> RADIUS", buf, len);
		ieee802_1x_encapsulate_radius(&eapol_test, buf, len);
	}
	return 0;
}