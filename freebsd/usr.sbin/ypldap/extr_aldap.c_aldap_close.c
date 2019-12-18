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
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;
struct aldap {TYPE_1__ ber; } ;

/* Variables and functions */
 int /*<<< orphan*/  ber_free (TYPE_1__*) ; 
 int close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct aldap*) ; 

int
aldap_close(struct aldap *al)
{
	if (close(al->ber.fd) == -1)
		return (-1);

	ber_free(&al->ber);
	free(al);

	return (0);
}