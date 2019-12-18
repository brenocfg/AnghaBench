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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_authenticator {int /*<<< orphan*/  cb_ctx; TYPE_1__* cb; } ;
typedef  int /*<<< orphan*/  logger_level ;
struct TYPE_2__ {int /*<<< orphan*/  (* logger ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char const*) ; 

void wpa_auth_logger(struct wpa_authenticator *wpa_auth, const u8 *addr,
		     logger_level level, const char *txt)
{
	if (wpa_auth->cb->logger == NULL)
		return;
	wpa_auth->cb->logger(wpa_auth->cb_ctx, addr, level, txt);
}