#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wps_registrar {TYPE_1__* wps; } ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  config_methods; } ;

/* Variables and functions */
 int wps_build_config_methods (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wps_build_config_methods_r(struct wps_registrar *reg,
				      struct wpabuf *msg)
{
	return wps_build_config_methods(msg, reg->wps->config_methods);
}