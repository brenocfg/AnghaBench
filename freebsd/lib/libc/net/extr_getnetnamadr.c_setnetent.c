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
struct netent_data {int dummy; } ;

/* Variables and functions */
 struct netent_data* __netent_data_init () ; 
 int /*<<< orphan*/  _setnetdnsent (int) ; 
 int /*<<< orphan*/  _setnethtent (int,struct netent_data*) ; 

void
setnetent(int stayopen)
{
	struct netent_data *ned;

	if ((ned = __netent_data_init()) == NULL)
		return;
	_setnethtent(stayopen, ned);
	_setnetdnsent(stayopen);
}