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
typedef  int /*<<< orphan*/  u_int32_t ;
struct tcphdr {int dummy; } ;
struct ip {int dummy; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct alias_link {int dummy; } ;
struct StartMediaTransmission {int /*<<< orphan*/  remoteIpAddr; } ;
typedef  int /*<<< orphan*/  ConvDirection ;

/* Variables and functions */

__attribute__((used)) static int
alias_skinny_startmedia(struct StartMediaTransmission *start_media,
    struct ip *pip, struct tcphdr *tc,
    struct alias_link *lnk, u_int32_t localIpAddr,
    ConvDirection direction)
{
	struct in_addr dst, src;

	(void)pip;
	(void)tc;
	(void)lnk;
	(void)direction;

	dst.s_addr = start_media->remoteIpAddr;
	src.s_addr = localIpAddr;

	/*
	 * XXX I should probably handle in bound global translations as
	 * well.
	 */

	return (0);
}