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
union key {int number; } ;
struct rpcent {int dummy; } ;

/* Variables and functions */
 struct rpcent* getrpc (int /*<<< orphan*/ ,union key) ; 
 int /*<<< orphan*/  wrap_getrpcbynumber_r ; 

struct rpcent *
getrpcbynumber(int number)
{
	union key key;

	key.number = number;

	return (getrpc(wrap_getrpcbynumber_r, key));
}