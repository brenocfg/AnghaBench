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
struct ksched {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_P31B ; 
 int /*<<< orphan*/  free (struct ksched*,int /*<<< orphan*/ ) ; 

int
ksched_detach(struct ksched *ks)
{

	free(ks, M_P31B);
	return (0);
}