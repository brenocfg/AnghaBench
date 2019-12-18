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
struct ntb_softc {int dummy; } ;
typedef  enum ntb_bar { ____Placeholder_ntb_bar } ntb_bar ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_FEATURE (struct ntb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int NTB_B2B_BAR_2 ; 
 int NTB_MAX_BARS ; 
 int /*<<< orphan*/  NTB_SPLIT_BAR ; 

__attribute__((used)) static inline bool
bar_is_64bit(struct ntb_softc *ntb, enum ntb_bar bar)
{
	/* XXX This assertion could be stronger. */
	KASSERT(bar < NTB_MAX_BARS, ("bogus bar"));
	return (bar < NTB_B2B_BAR_2 || !HAS_FEATURE(ntb, NTB_SPLIT_BAR));
}