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
typedef  int u32 ;
struct factors_request {int parent_rate; int rate; int p; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int order_base_2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun9i_a80_get_ahb_factors(struct factors_request *req)
{
	u32 _p;

	if (req->parent_rate < req->rate)
		req->rate = req->parent_rate;

	_p = order_base_2(DIV_ROUND_UP(req->parent_rate, req->rate));

	/* maximum p is 3 */
	if (_p > 3)
		_p = 3;

	req->rate = req->parent_rate >> _p;
	req->p = _p;
}