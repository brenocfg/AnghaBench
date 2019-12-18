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
typedef  int /*<<< orphan*/  uv_passwd_t ;

/* Variables and functions */
 int uv__getpwuid_r (int /*<<< orphan*/ *) ; 

int uv_os_get_passwd(uv_passwd_t* pwd) {
  return uv__getpwuid_r(pwd);
}