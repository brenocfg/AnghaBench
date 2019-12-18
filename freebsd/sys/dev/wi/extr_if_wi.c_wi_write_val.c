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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct wi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int wi_write_rid (struct wi_softc*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __inline int
wi_write_val(struct wi_softc *sc, int rid, u_int16_t val)
{

	val = htole16(val);
	return wi_write_rid(sc, rid, &val, sizeof(val));
}