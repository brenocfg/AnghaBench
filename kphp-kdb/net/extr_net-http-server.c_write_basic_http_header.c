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
struct hts_data {scalar_t__ http_ver; int query_flags; } ;
struct connection {int /*<<< orphan*/  Out; } ;

/* Variables and functions */
 int B_SZ ; 
 struct hts_data* HTS_DATA (struct connection*) ; 
 scalar_t__ HTTP_V10 ; 
 int QF_KEEPALIVE ; 
 int /*<<< orphan*/  assert (int) ; 
 char* cur_http_date () ; 
 int /*<<< orphan*/  gen_http_date (char*,int) ; 
 char* header_pattern ; 
 char* http_get_error_msg_text (int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char const*,char*,char const*,char*,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int write_out (int /*<<< orphan*/ *,char*,int) ; 

int write_basic_http_header (struct connection *c, int code, int date, int len, const char *add_header, const char *content_type) {
  struct hts_data *D = HTS_DATA(c);

  if (D->http_ver >= HTTP_V10) {
#define B_SZ	2048
    static char buff[B_SZ], date_buff[32];
    char *ptr = buff;
    const char *error_message = http_get_error_msg_text (&code);
    if (date) {
      gen_http_date (date_buff, date);
    }
    ptr += snprintf (ptr, B_SZ - 64, header_pattern, code, error_message,
		    date ? date_buff : cur_http_date(), content_type ? content_type : "text/html", (D->query_flags & QF_KEEPALIVE) ? "keep-alive" : "close", add_header ? add_header : "");
    assert (ptr < buff + B_SZ - 64);
    if (len >= 0) {
      ptr += sprintf (ptr, "Content-Length: %d\r\n", len);
    }

    ptr += sprintf (ptr, "\r\n");

    return write_out (&c->Out, buff, ptr - buff);
  }

  return 0;
}