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
struct regnode_std_param {int dummy; } ;
struct regnode {struct regnode_std_param std_param; } ;

/* Variables and functions */

struct regnode_std_param *regnode_get_stdparam(struct regnode *regnode)
{

	return (&regnode->std_param);
}