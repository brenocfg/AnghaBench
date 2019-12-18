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
typedef  int u8 ;

/* Variables and functions */
 char const* openssl_content_type (int const) ; 

__attribute__((used)) static const char * openssl_handshake_type(int content_type, const u8 *buf,
					   size_t len)
{
	if (content_type == 257 && buf && len == 1)
		return openssl_content_type(buf[0]);
	if (content_type != 22 || !buf || len == 0)
		return "";
	switch (buf[0]) {
	case 0:
		return "hello request";
	case 1:
		return "client hello";
	case 2:
		return "server hello";
	case 3:
		return "hello verify request";
	case 4:
		return "new session ticket";
	case 5:
		return "end of early data";
	case 6:
		return "hello retry request";
	case 8:
		return "encrypted extensions";
	case 11:
		return "certificate";
	case 12:
		return "server key exchange";
	case 13:
		return "certificate request";
	case 14:
		return "server hello done";
	case 15:
		return "certificate verify";
	case 16:
		return "client key exchange";
	case 20:
		return "finished";
	case 21:
		return "certificate url";
	case 22:
		return "certificate status";
	case 23:
		return "supplemental data";
	case 24:
		return "key update";
	case 254:
		return "message hash";
	default:
		return "?";
	}
}