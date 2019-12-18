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
struct rtadvd_timer {int dummy; } ;
struct prefix {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_prefix (struct prefix*) ; 

__attribute__((used)) static struct rtadvd_timer *
prefix_timeout(void *arg)
{

	delete_prefix((struct prefix *)arg);

	return (NULL);
}