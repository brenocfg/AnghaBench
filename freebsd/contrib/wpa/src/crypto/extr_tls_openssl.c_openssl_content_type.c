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

/* Variables and functions */

__attribute__((used)) static const char * openssl_content_type(int content_type)
{
	switch (content_type) {
	case 20:
		return "change cipher spec";
	case 21:
		return "alert";
	case 22:
		return "handshake";
	case 23:
		return "application data";
	case 24:
		return "heartbeat";
	case 256:
		return "TLS header info"; /* pseudo content type */
	case 257:
		return "inner content type"; /* pseudo content type */
	default:
		return "?";
	}
}