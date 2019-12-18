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
typedef  int uint64_t ;
typedef  scalar_t__ u_int ;
struct ahd_softc {int dummy; } ;

/* Variables and functions */
 int ahd_inl_scbram (struct ahd_softc*,scalar_t__) ; 

__attribute__((used)) static __inline uint64_t
ahd_inq_scbram(struct ahd_softc *ahd, u_int offset)
{
	return (ahd_inl_scbram(ahd, offset)
	      | ((uint64_t)ahd_inl_scbram(ahd, offset+4)) << 32);
}