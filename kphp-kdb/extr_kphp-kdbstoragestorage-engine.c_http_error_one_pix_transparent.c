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
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ct_png ; 
 int /*<<< orphan*/  one_pix_transparent_errors ; 
 int /*<<< orphan*/  write_http_doc (struct connection*,void*,int,int,int /*<<< orphan*/ ) ; 

int http_error_one_pix_transparent (struct connection *c) {
  one_pix_transparent_errors++;
  static const unsigned char one_pix_transparent_png[82] = {
    137, 80, 78, 71, 13, 10, 26, 10, 0, 0, 0, 13, 73, 72, 68, 82,
    0, 0, 0, 1, 0, 0, 0, 1, 8, 4, 0, 0, 0, 181, 28, 12,
    2, 0, 0, 0, 2, 98, 75, 71, 68, 0, 0, 170, 141, 35, 50, 0,
    0, 0, 11, 73, 68, 65, 84, 8, 215, 99, 96, 96, 0, 0, 0, 3,
    0, 1, 32, 213, 148, 199, 0, 0, 0, 0, 73, 69, 78, 68, 174, 66,
    96, 130
  };
  write_http_doc (c, (void *) one_pix_transparent_png, 82, 545774400, ct_png);
  return 0;
}