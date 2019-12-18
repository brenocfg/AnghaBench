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
typedef  scalar_t__ u_int ;
typedef  int u_char ;
struct uni_msg {int dummy; } ;
struct uni_addr {int type; int plan; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
typedef  enum uni_addr_screen { ____Placeholder_uni_addr_screen } uni_addr_screen ;
typedef  enum uni_addr_pres { ____Placeholder_uni_addr_pres } uni_addr_pres ;

/* Variables and functions */
 int /*<<< orphan*/  APP_BUF (struct uni_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APP_BYTE (struct uni_msg*,int) ; 

__attribute__((used)) static void
encode_addr(struct uni_msg *msg, struct uni_addr *addr, u_int flag,
    enum uni_addr_screen screen, enum uni_addr_pres pres, int err)
{
	u_char ext = err ? 0x00 : 0x80;

	if (flag) {
		APP_BYTE(msg, (addr->type << 4) | addr->plan);
		APP_BYTE(msg, ext | (pres << 5) | (screen));
	} else {
		APP_BYTE(msg, ext | (addr->type << 4) | addr->plan);
	}
	APP_BUF(msg, addr->addr, addr->len);
}