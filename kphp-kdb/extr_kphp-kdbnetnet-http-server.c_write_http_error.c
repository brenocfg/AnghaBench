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
struct connection {int /*<<< orphan*/  Out; } ;

/* Variables and functions */
 char* error_text_pattern ; 
 char* http_get_error_msg_text (int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,char const*,int,char const*) ; 
 int /*<<< orphan*/  write_basic_http_header (struct connection*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int write_out (int /*<<< orphan*/ *,char*,int) ; 

int write_http_error (struct connection *c, int code) {
  if (code == 204) {
    write_basic_http_header (c, code, 0, -1, 0, 0);
    return 0;
  } else {
    static char buff[1024];
    char *ptr = buff;
    const char *error_message = http_get_error_msg_text (&code);
    ptr += sprintf (ptr, error_text_pattern, code, error_message, code, error_message);
    write_basic_http_header (c, code, 0, ptr - buff, 0, 0);
    return write_out (&c->Out, buff, ptr - buff);
  }
}