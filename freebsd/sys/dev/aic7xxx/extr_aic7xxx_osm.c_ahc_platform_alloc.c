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
struct ahc_softc {int /*<<< orphan*/ * platform_data; } ;
struct ahc_platform_data {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 

int
ahc_platform_alloc(struct ahc_softc *ahc, void *platform_arg)
{
	ahc->platform_data = malloc(sizeof(struct ahc_platform_data), M_DEVBUF,
	    M_NOWAIT | M_ZERO);
	if (ahc->platform_data == NULL)
		return (ENOMEM);
	return (0);
}