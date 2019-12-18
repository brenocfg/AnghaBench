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
typedef  int /*<<< orphan*/  len_buf ;

/* Variables and functions */
 int /*<<< orphan*/  os_memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  os_strlen (char*) ; 
 int /*<<< orphan*/  soap_postfix ; 
 int /*<<< orphan*/  wpabuf_printf (struct wpabuf*,char*,char const*) ; 
 scalar_t__ wpabuf_put (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wps_er_soap_end(struct wpabuf *buf, const char *name,
			    char *len_ptr, char *body_ptr)
{
	char len_buf[10];
	wpabuf_printf(buf, "</u:%s>\n", name);
	wpabuf_put_str(buf, soap_postfix);
	os_snprintf(len_buf, sizeof(len_buf), "%d",
		    (int) ((char *) wpabuf_put(buf, 0) - body_ptr));
	os_memcpy(len_ptr, len_buf, os_strlen(len_buf));
}