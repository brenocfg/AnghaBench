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
struct utmpx {int dummy; } ;
struct logininfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  endutxent () ; 
 int /*<<< orphan*/  pututxline (struct utmpx*) ; 
 int /*<<< orphan*/  setutxent () ; 

__attribute__((used)) static int
utmpx_write_library(struct logininfo *li, struct utmpx *utx)
{
	setutxent();
	pututxline(utx);

#  ifdef HAVE_ENDUTXENT
	endutxent();
#  endif
	return (1);
}