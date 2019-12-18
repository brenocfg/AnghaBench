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
struct wpabuf {int dummy; } ;

/* Variables and functions */
 struct wpabuf* ndef_parse_records (struct wpabuf const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wifi_filter ; 

struct wpabuf * ndef_parse_wifi(const struct wpabuf *buf)
{
	return ndef_parse_records(buf, wifi_filter);
}