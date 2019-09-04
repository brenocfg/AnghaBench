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
struct pollfd {int dummy; } ;
struct io_pump {scalar_t__ error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (struct pollfd*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (struct pollfd*) ; 
 scalar_t__ pump_io_round (struct io_pump*,int,struct pollfd*) ; 

__attribute__((used)) static int pump_io(struct io_pump *slots, int nr)
{
	struct pollfd *pfd;
	int i;

	for (i = 0; i < nr; i++)
		slots[i].error = 0;

	ALLOC_ARRAY(pfd, nr);
	while (pump_io_round(slots, nr, pfd))
		; /* nothing */
	free(pfd);

	/* There may be multiple errno values, so just pick the first. */
	for (i = 0; i < nr; i++) {
		if (slots[i].error) {
			errno = slots[i].error;
			return -1;
		}
	}
	return 0;
}