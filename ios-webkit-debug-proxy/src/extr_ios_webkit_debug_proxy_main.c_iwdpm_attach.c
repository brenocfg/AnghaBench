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
typedef  int /*<<< orphan*/  iwdp_t ;

/* Variables and functions */
 int wi_connect (char const*,char**,char**,int*,void**,int) ; 

int iwdpm_attach(iwdp_t iwdp, const char *device_id, char **to_device_id,
    char **to_device_name, int *to_device_os_version, void **to_ssl_session) {
  return wi_connect(device_id, to_device_id, to_device_name,
      to_device_os_version, to_ssl_session, -1);
}