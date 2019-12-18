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
struct xnb_pkt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct xnb_pkt*,int) ; 

__attribute__((used)) static inline void
xnb_pkt_initialize(struct xnb_pkt *pxnb)
{
	bzero(pxnb, sizeof(*pxnb));
}