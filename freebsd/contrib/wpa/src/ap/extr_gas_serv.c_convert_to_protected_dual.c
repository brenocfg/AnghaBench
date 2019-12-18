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
 int /*<<< orphan*/  WLAN_ACTION_PROTECTED_DUAL ; 
 int /*<<< orphan*/ * wpabuf_mhead_u8 (struct wpabuf*) ; 

__attribute__((used)) static void convert_to_protected_dual(struct wpabuf *msg)
{
	u8 *categ = wpabuf_mhead_u8(msg);
	*categ = WLAN_ACTION_PROTECTED_DUAL;
}