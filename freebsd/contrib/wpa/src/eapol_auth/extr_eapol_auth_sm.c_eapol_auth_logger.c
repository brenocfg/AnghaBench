#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* logger ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char const*) ;} ;
struct eapol_authenticator {TYPE_2__ conf; TYPE_1__ cb; } ;
typedef  int /*<<< orphan*/  eapol_logger_level ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void eapol_auth_logger(struct eapol_authenticator *eapol,
			      const u8 *addr, eapol_logger_level level,
			      const char *txt)
{
	if (eapol->cb.logger == NULL)
		return;
	eapol->cb.logger(eapol->conf.ctx, addr, level, txt);
}