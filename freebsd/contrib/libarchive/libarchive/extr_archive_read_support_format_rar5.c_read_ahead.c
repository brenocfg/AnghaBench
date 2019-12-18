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
typedef  int /*<<< orphan*/  uint8_t ;
struct archive_read {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/ * __archive_read_ahead (struct archive_read*,size_t,int*) ; 

__attribute__((used)) static int read_ahead(struct archive_read* a, size_t how_many,
    const uint8_t** ptr)
{
	if(!ptr)
		return 0;

	ssize_t avail = -1;
	*ptr = __archive_read_ahead(a, how_many, &avail);
	if(*ptr == NULL) {
		return 0;
	}

	return 1;
}