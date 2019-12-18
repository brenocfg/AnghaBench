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
typedef  scalar_t__ time_t ;
struct fifolog_writer {int dummy; } ;

/* Variables and functions */
 int fifolog_write_gzip (struct fifolog_writer*,scalar_t__) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 

int
fifolog_write_poll(struct fifolog_writer *f, time_t now)
{

	if (now == 0)
		time(&now);
	return (fifolog_write_gzip(f, now));
}