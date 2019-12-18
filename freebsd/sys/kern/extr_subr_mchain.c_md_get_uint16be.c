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
typedef  int /*<<< orphan*/  uint16_t ;
struct mdchain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16toh (int /*<<< orphan*/ ) ; 
 int md_get_uint16 (struct mdchain*,int /*<<< orphan*/ *) ; 

int
md_get_uint16be(struct mdchain *mdp, uint16_t *x)
{
	uint16_t v;
	int error = md_get_uint16(mdp, &v);

	if (x != NULL)
		*x = be16toh(v);
	return (error);
}