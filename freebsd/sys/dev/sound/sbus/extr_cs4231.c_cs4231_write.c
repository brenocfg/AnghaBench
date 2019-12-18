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
typedef  int /*<<< orphan*/  u_int8_t ;
struct cs4231_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4231_IADDR ; 
 int /*<<< orphan*/  CS4231_IDATA ; 
 int /*<<< orphan*/  CS_WRITE (struct cs4231_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cs4231_write(struct cs4231_softc *sc, u_int8_t r, u_int8_t v)
{
	CS_WRITE(sc, CS4231_IADDR, r);
	CS_WRITE(sc, CS4231_IDATA, v);
}