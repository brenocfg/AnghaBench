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
 int /*<<< orphan*/  no_cache_headers ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  write_basic_http_header (struct connection*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char const*,int) ; 

void http_return (struct connection *c, const char *str, int len) {
  if (len < 0) {
    len = (int)strlen (str);
  }
  write_basic_http_header (c, 200, 0, len, no_cache_headers, "text/javascript; charset=UTF-8");
  write_out (&c->Out, str, len);
}