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
 int conv_hex_digit (char) ; 
 int /*<<< orphan*/  md5_hex (char*,int,char*) ; 
 int strlen (char*) ; 

int md5_last_bits (char *x) {
  char md5_buf[32];
  int l = strlen (x);
  md5_hex (x, l, md5_buf);

  return conv_hex_digit (md5_buf[29]) * 256 + conv_hex_digit (md5_buf[30]) * 16 + conv_hex_digit (md5_buf[31]);
}