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
struct namedobj_instance {int dummy; } ;
struct named_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IPFW ; 
 int /*<<< orphan*/  free (struct named_object*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
destroy_iface(struct namedobj_instance *ii, struct named_object *no,
    void *arg)
{

	/* Assume all consumers have been already detached */
	free(no, M_IPFW);
	return (0);
}