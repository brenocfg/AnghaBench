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
typedef  scalar_t__ money_auth_code_t ;

/* Variables and functions */
 int /*<<< orphan*/  md5_hex (char*,int,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 
 scalar_t__ strtoull (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 
 char xor_hcyf (char,char) ; 

__attribute__((used)) static int check_signature (char auth_signature[32], char *temp, int L, money_auth_code_t code) {
  int i;
  if (!auth_signature) {
    return 0;
  }
  sprintf (temp + L, "%016llx", code);
  md5_hex (temp, L + 16, temp + L + 16);
  vkprintf (1, "in check_signature: md5_hex(%.*s)=%.32s, xor with %.32s\n", L+16, temp, temp+L+16, auth_signature);
  for (i = 0; i < 32; i++) {
    temp[L+16+i] = xor_hcyf (temp[L+16+i], auth_signature[i]);
  }
  md5_hex (temp + L + 16, 32, temp + L + 48);
  vkprintf (1, "xor=%.32s, md5(xor)=%.16s\n", temp+L+16, temp+L+48);
  temp[L+64] = 0;
  return strtoull (temp + L + 48, 0, 16) == code; 
}