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
struct uath_softc {int dummy; } ;

/* Variables and functions */
 int uath_cmdflush (struct uath_softc*) ; 
 int uath_dataflush (struct uath_softc*) ; 

__attribute__((used)) static int
uath_flush(struct uath_softc *sc)
{
	int error;

	error = uath_dataflush(sc);
	if (error != 0)
		goto failed;

	error = uath_cmdflush(sc);
	if (error != 0)
		goto failed;

failed:
	return (error);
}