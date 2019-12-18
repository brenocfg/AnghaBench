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
struct servent {int dummy; } ;
struct key {scalar_t__ port; int /*<<< orphan*/ * proto; } ;

/* Variables and functions */
 struct servent* getserv (int /*<<< orphan*/ ,struct key) ; 
 int /*<<< orphan*/  wrap_getservent_r ; 

struct servent *
getservent(void)
{
	struct key key;

	key.proto = NULL;
	key.port = 0;

	return (getserv(wrap_getservent_r, key));
}