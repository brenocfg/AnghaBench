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
typedef  int /*<<< orphan*/  u_int ;
struct ahd_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HESCB_QOFF ; 
 int /*<<< orphan*/  ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline u_int
ahd_get_hescb_qoff(struct ahd_softc *ahd)
{
	return (ahd_inb(ahd, HESCB_QOFF));
}