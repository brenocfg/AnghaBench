#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int fd; } ;
struct aldap {TYPE_1__ ber; } ;

/* Variables and functions */
 struct aldap* calloc (int,int) ; 

struct aldap *
aldap_init(int fd)
{
	struct aldap *a;

	if ((a = calloc(1, sizeof(*a))) == NULL)
		return NULL;
	a->ber.fd = fd;

	return a;
}