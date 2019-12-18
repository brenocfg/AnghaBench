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
struct socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  socantsendmore (struct socket*) ; 
 int /*<<< orphan*/ * sotorawcb (struct socket*) ; 

__attribute__((used)) static int
raw_ushutdown(struct socket *so)
{

	KASSERT(sotorawcb(so) != NULL, ("raw_ushutdown: rp == NULL"));

	socantsendmore(so);
	return (0);
}