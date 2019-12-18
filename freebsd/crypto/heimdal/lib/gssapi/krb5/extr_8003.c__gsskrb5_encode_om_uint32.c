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
typedef  int u_char ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int OM_uint32 ;

/* Variables and functions */

krb5_error_code
_gsskrb5_encode_om_uint32(OM_uint32 n, u_char *p)
{
  p[0] = (n >> 0)  & 0xFF;
  p[1] = (n >> 8)  & 0xFF;
  p[2] = (n >> 16) & 0xFF;
  p[3] = (n >> 24) & 0xFF;
  return 0;
}