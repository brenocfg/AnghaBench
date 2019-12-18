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
struct lockd_ans {int la_vers; } ;

/* Variables and functions */
 int /*<<< orphan*/  devfd ; 
 scalar_t__ write (int /*<<< orphan*/ ,struct lockd_ans*,int) ; 

__attribute__((used)) static int
nfslockdans(int vers, struct lockd_ans *ansp)
{

	ansp->la_vers = vers;
	return (write(devfd, ansp, sizeof *ansp) <= 0);
}