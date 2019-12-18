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
struct creation_set {int dummy; } ;

/* Variables and functions */
 struct creation_set* calloc (int,int) ; 

struct creation_set *
cset_new(void)
{
	return calloc(1, sizeof(struct creation_set));
}