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
typedef  int /*<<< orphan*/  uint64_t ;
struct tcp_bbr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bbr_get_bw (struct tcp_bbr*) ; 

__attribute__((used)) static inline uint64_t
bbr_get_bw(struct tcp_bbr *bbr)
{
	uint64_t bw;

	bw = __bbr_get_bw(bbr);
	return (bw);
}