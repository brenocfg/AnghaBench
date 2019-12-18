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
 int /*<<< orphan*/  WDCMSG_FLUSH ; 
 int uath_cmd_write (struct uath_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uath_cmdflush(struct uath_softc *sc)
{

	return uath_cmd_write(sc, WDCMSG_FLUSH, NULL, 0, 0);
}