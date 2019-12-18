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
struct reset_controller_dev {int dummy; } ;
struct gemini_reset {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int BIT (unsigned long) ; 
 int /*<<< orphan*/  GEMINI_GLOBAL_SOFT_RESET ; 
 unsigned long GEMINI_RESET_CPU1 ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct gemini_reset* to_gemini_reset (struct reset_controller_dev*) ; 

__attribute__((used)) static int gemini_reset(struct reset_controller_dev *rcdev,
			unsigned long id)
{
	struct gemini_reset *gr = to_gemini_reset(rcdev);

	/* Manual says to always set BIT 30 (CPU1) to 1 */
	return regmap_write(gr->map,
			    GEMINI_GLOBAL_SOFT_RESET,
			    BIT(GEMINI_RESET_CPU1) | BIT(id));
}