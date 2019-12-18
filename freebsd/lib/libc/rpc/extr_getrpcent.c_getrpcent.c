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
union key {scalar_t__ number; } ;
struct rpcent {int dummy; } ;

/* Variables and functions */
 struct rpcent* getrpc (int /*<<< orphan*/ ,union key) ; 
 int /*<<< orphan*/  wrap_getrpcent_r ; 

struct rpcent *
getrpcent(void)
{
	union key key;

	key.number = 0;	/* not used */

	return (getrpc(wrap_getrpcent_r, key));
}