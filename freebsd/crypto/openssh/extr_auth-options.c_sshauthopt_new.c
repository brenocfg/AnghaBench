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
struct sshauthopt {int force_tun_device; } ;

/* Variables and functions */
 struct sshauthopt* calloc (int,int) ; 

struct sshauthopt *
sshauthopt_new(void)
{
	struct sshauthopt *ret;

	if ((ret = calloc(1, sizeof(*ret))) == NULL)
		return NULL;
	ret->force_tun_device = -1;
	return ret;
}