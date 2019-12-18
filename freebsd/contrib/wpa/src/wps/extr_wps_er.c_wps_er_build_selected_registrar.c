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
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int ATTR_SELECTED_REGISTRAR ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

__attribute__((used)) static int wps_er_build_selected_registrar(struct wpabuf *msg, int sel_reg)
{
	wpabuf_put_be16(msg, ATTR_SELECTED_REGISTRAR);
	wpabuf_put_be16(msg, 1);
	wpabuf_put_u8(msg, !!sel_reg);
	return 0;
}