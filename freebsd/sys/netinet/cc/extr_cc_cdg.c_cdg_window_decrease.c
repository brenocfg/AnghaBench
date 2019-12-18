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
typedef  unsigned int uint32_t ;
struct cc_var {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCV (struct cc_var*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_wnd ; 
 unsigned int ulmin (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static inline uint32_t
cdg_window_decrease(struct cc_var *ccv, unsigned long owin, unsigned int beta)
{

	return ((ulmin(CCV(ccv, snd_wnd), owin) * beta) / 100);
}