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
 int /*<<< orphan*/ * ContentTypes ; 
 int /*<<< orphan*/  gen_http_date (char*,int) ; 
 int /*<<< orphan*/  write_basic_http_header (struct connection*,int,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,void*,int) ; 

__attribute__((used)) static void write_http_doc (struct connection *c, void *data, int size, int mtime, int content_type) {
  static char headers[128] =
    "Expires: Thu, 31 Dec 2037 23:55:55 GMT\r\n"
    "Cache-Control: max-age=315360000\r\n"
    "Last-Modified: *****************************\r\n";
  gen_http_date (headers + (40 + 34 + 15), mtime);
  write_basic_http_header (c, 200, 0, size, headers, ContentTypes[content_type]);
  write_out (&c->Out, data, size);
}