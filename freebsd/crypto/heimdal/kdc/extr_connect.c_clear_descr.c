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
struct descr {scalar_t__ s; scalar_t__ len; int /*<<< orphan*/  size; scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rk_INVALID_SOCKET ; 
 int /*<<< orphan*/  rk_closesocket (scalar_t__) ; 

__attribute__((used)) static void
clear_descr(struct descr *d)
{
    if(d->buf)
	memset(d->buf, 0, d->size);
    d->len = 0;
    if(d->s != rk_INVALID_SOCKET)
	rk_closesocket(d->s);
    d->s = rk_INVALID_SOCKET;
}