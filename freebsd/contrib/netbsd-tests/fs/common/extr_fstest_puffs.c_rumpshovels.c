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
struct puffstestargs {int dummy; } ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct puffstestargs*) ; 
 int /*<<< orphan*/  pthread_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readshovel ; 
 int rump_init () ; 
 int /*<<< orphan*/  writeshovel ; 

__attribute__((used)) static void
rumpshovels(struct puffstestargs *args)
{
	pthread_t pt;
	int rv;

	if ((rv = rump_init()) == -1)
		err(1, "rump_init");

	if (pthread_create(&pt, NULL, readshovel, args) == -1)
		err(1, "read shovel");
	pthread_detach(pt);

	if (pthread_create(&pt, NULL, writeshovel, args) == -1)
		err(1, "write shovel");
	pthread_detach(pt);
}