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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_UUID_R ; 
 int /*<<< orphan*/  WPS_UUID_LEN ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wps_er_build_uuid_r(struct wpabuf *msg, const u8 *uuid_r)
{
	wpabuf_put_be16(msg, ATTR_UUID_R);
	wpabuf_put_be16(msg, WPS_UUID_LEN);
	wpabuf_put_data(msg, uuid_r, WPS_UUID_LEN);
	return 0;
}