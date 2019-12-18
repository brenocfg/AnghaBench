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
struct thread {int dummy; } ;
struct md_s {int mediasize; } ;
struct md_req {int dummy; } ;

/* Variables and functions */
 int EDOM ; 
 int PAGE_SIZE ; 

__attribute__((used)) static int
mdcreate_null(struct md_s *sc, struct md_req *mdr, struct thread *td)
{

	/*
	 * Range check.  Disallow negative sizes and sizes not being
	 * multiple of page size.
	 */
	if (sc->mediasize <= 0 || (sc->mediasize % PAGE_SIZE) != 0)
		return (EDOM);

	return (0);
}