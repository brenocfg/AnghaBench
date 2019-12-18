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
struct fha_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fha_uninit (struct fha_params*) ; 
 struct fha_params fhanew_softc ; 

__attribute__((used)) static void
fhanew_uninit(void *foo)
{
	struct fha_params *softc;

	softc = &fhanew_softc;

	fha_uninit(softc);
}