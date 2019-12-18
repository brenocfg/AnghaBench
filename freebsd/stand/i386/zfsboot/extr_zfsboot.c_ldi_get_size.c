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
typedef  int uint64_t ;
struct TYPE_2__ {int size; scalar_t__ start; } ;
struct zfsdsk {TYPE_1__ dsk; } ;

/* Variables and functions */
 int DEV_BSIZE ; 
 int drvsize_ext (struct zfsdsk*) ; 

uint64_t
ldi_get_size(void *priv)
{
	struct zfsdsk *zdsk = priv;
	uint64_t size = zdsk->dsk.size;

	if (zdsk->dsk.start == 0)
		size = drvsize_ext(zdsk);

	return (size * DEV_BSIZE);
}